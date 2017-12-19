#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Light {
	vec3 position;
	//vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform Light light;
uniform sampler2D floorTexture;
uniform vec3 viewPos;
uniform bool blinn;

void main()
{
	
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	vec3 ambient = light.ambient * texture(floorTexture, TexCoords).rgb;
	
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse =  diff * texture(floorTexture, TexCoords).rgb;

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	
	float spec = 0.0;
	if (blinn)
	{
		vec3 halfwayDir = normalize(lightDir + viewDir);
		spec = pow(max(dot(norm, halfwayDir ), 0.0), 16.0/*shininess*/ );
	}
	else
	{	
		vec3 reflectDir = reflect(-lightDir, norm);
		spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
	}
	
	vec3 specular = light.specular * spec;
    
	ambient  *= attenuation;
	diffuse  *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);	
}