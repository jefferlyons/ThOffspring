#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

struct Light {
    vec3 Position;
    vec3 Color;
};

uniform Light lights[4];
uniform sampler2D diffuseTexture;
uniform vec3 viewPos;

void main()
{
    
    vec3 normal =  normalize(fs_in.Normal);
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
        
    vec3 ambient = 0.0 * color;
    // lighting
    vec3 lighting = vec3(0.0);
    for(int i = 0; i < 4; i++) 
    {
        //diffuse
        vec3 lightDir = normalize(lights[i].Position - fs_in.FragPos);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = diff * lights[i].Color * color;
        //specular
        float spec = 0.0;
        vec3 viewDir = normalize(viewPos - fs_in.FragPos);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), 95.0 );
        vec3 specular = spec * vec3(0.0);   

        //final color
        vec3 result  = diffuse + specular;
        float distance = length(fs_in.FragPos - lights[i].Position);
        result *= 1.0 / (distance * distance);
        lighting += result;
    }
    
    FragColor = vec4(ambient + lighting , 1.0);
    //FragColor = vec4(vec3(shadow / far_plane), 1.0);
}