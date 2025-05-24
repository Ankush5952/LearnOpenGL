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
	vec3 dir;

	vec3 spotDir;
	float spotCutoff;
	float outerCutoff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float Kc; //constant 
	float Kl; //linear constant
	float Kq; //quadratic constant
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
	vec3 lightDir;
	float attenuation = 1.0f;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 emission;

	lightDir = normalize(light.dir - fragPos);

	float theta = dot(lightDir,normalize(-light.spotDir));
	float epsilon = light.spotCutoff - light.outerCutoff; //E = phi - y
	float intensity = clamp((theta - light.outerCutoff)/epsilon,0.0,1.0); //I = (o - y)/phi - y = (o - y)/E

	if(theta > light.spotCutoff)
	{
		//ambient
		ambient =texture(mat.diffuse,texcoords).rgb * light.ambient;

		//diffuse
		vec3 norm = normalize(normal);
		float diff = max(dot(norm,lightDir),0.0f);
		diffuse = light.diffuse * diff * texture(mat.diffuse,texcoords).rgb;

		//specular
		vec3 viewDir = normalize(viewPos - fragPos);
		vec3 reflectDir = reflect(-lightDir,norm);
		float spec = pow(max(dot(viewDir,reflectDir),0.0f),mat.shininess);
		specular = spec * texture(mat.specular,texcoords).rgb * light.specular;

		//emission
		float emissionStr = 0.0f;
		emission = emissionStr * texture(mat.emission,texcoords).rgb;

		//attenuation
		float d = length(light.dir - fragPos);
		attenuation = 1.0f/(light.Kc + light.Kl*d + light.Kq*d*d);

		diffuse *= attenuation * intensity;
		specular *= attenuation * intensity;
		emission *= attenuation;

		vec3 result = (diffuse + ambient + specular + emission) * objClr;

		fragclr = vec4(result, 1.0f);
	}else
	{
		//ambient
		ambient = texture(mat.diffuse,texcoords).rgb * light.ambient;
		//emission
		float emissionStr = 0.0f;
		emission = emissionStr * vec3(texture(mat.emission,texcoords));

		fragclr = vec4((ambient+emission)*objClr ,1.0f);
	}
}