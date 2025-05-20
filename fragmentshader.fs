#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffusion;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 pos;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

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
	vec3 ambient =mat.ambient*light.ambient;

	//diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.pos - fragPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = mat.diffusion * diff * light.diffuse;

	//specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),mat.shininess);
	vec3 specular = spec * mat.specular * light.specular;

	vec3 result = (diffuse + ambient + specular) * objClr;

	fragclr = vec4(result, 1.0f);
}