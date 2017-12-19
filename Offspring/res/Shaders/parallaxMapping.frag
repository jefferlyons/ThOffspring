#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;
uniform sampler2D depthMap; 
uniform samplerCube shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float far_plane;
uniform float height_scale;

vec2 ParrallaxMapping(vec2 TexCoords , vec3 viewDir)
{
    //number if depth layers
    const float minLayers = 8;
    const float maxLayers = 32;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0,0.0, 1.0), viewDir)));
    //calulate tehe size 
    float layerDepth = 1.0 / numLayers; 
    // depth of current layer 
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (form vector P)
    vec2 P = viewDir.xy / viewDir.z * height_scale;
    vec2 deltaTexCoords = P / numLayers;
    // get initial values
    vec2 currentTexCoords = TexCoords;
    float currentDepthMapValue = texture(depthMap, currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue)
    {
        //shift texture coordinates along direction of P 
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(depthMap, currentTexCoords).r;
        // get depth of next layer
        currentLayerDepth += layerDepth;
    }

    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(depthMap, prevTexCoords).r - currentLayerDepth + layerDepth;

    // interpolation of texture coordinates 
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}

vec3 sampleOffsetDirections[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float ShadowCalculation(vec3 FragPos , vec3 lightDir , vec3 normal) 
{   
    vec3 fragToLight = FragPos - lightPos;
    
    //float closestDepth = texture(shadowMap, fragToLight).r;
    
    //closestDepth *= far_plane;
    float currentDepth = length(fragToLight);
     
	float bias    = 0.15;
    float shadow  = 0.0;
    int samples   = 20;
    float viewDistance = length(viewPos - FragPos);
    float diskRadius   = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(shadowMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
        closestDepth *= far_plane;
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
	shadow /= float(samples);

	return shadow;
}

void main()
{
    // offset texture coordinates with parallax Mapping
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec2 texCoords = ParrallaxMapping(fs_in.TexCoords , viewDir);

    if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
        discard;
    vec3 color = texture(diffuseTexture, texCoords).rgb;
    vec3 normal = texture(normalTexture, texCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    vec3 lightColor = vec3(1.0);
    //ambient
    vec3 ambient = 0.15 * color;
    //diffuse
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    //specular
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0 );
    vec3 specular = spec * lightColor;
    //calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPos , lightDir , normal);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

    FragColor = vec4(lighting , 1.0);
    //FragColor = vec4(vec3(shadow / far_plane), 1.0);
}