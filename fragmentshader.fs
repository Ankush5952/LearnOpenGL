#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light
{
	vec3 pos;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 texcoords;
in vec3 normal;
in vec3 fragPos;

uniform Material mat;

uniform Light light;

uniform vec3 objClr;
uniform vec3 viewPos;

out vec4 fragclr;

void main()
{
	//ambient
	vec3 ambient =vec3(texture(mat.diffuse,texcoords))*light.ambient;

	//diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.pos - fragPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(mat.diffuse,texcoords));

	//specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),mat.shininess);
	vec3 specular = spec * vec3(texture(mat.specular,texcoords)) * light.specular;

	//emission
	float emissionStr = 0.5f;
	vec3 emission = emissionStr * vec3(texture(mat.emission,texcoords));

	vec3 result = (diffuse + ambient + specular + emission) * objClr;

	fragclr = vec4(result, 1.0f);
}