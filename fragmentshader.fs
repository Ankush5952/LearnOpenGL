#version 330 core

in vec3 normal;
in vec3 fragPos;

uniform vec3 lightPos;
uniform vec3 objClr;
uniform vec3 lightClr;
uniform vec3 viewPos;

out vec4 fragclr;

void main()
{
	//diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = diff*lightClr;

	//specular
	float specularIntensity = 0.5f;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),32);
	vec3 specular = spec * specularIntensity * lightClr;

	//ambient
	float ambientStrength = 0.1;
	vec3 ambient =ambientStrength*lightClr;

	vec3 result = (diffuse + ambient + specular) * objClr;

	fragclr = vec4(result, 1.0f);
}