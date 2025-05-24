#version 330 core

//structs
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct DirLight
{
	bool on;

	vec3 dir;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	bool on;

	vec3 pos;

	float Kc;
	float Kl;
	float Kq;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight
{
	bool on;

	vec3 pos;
	vec3 dir;

	float cutoff;
	float outerCutoff;

	float Kc;
	float Kq;
	float Kl;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

//inputs
in vec2 texcoords;
in vec3 normal;
in vec3 fragPos;

//uniforms
uniform Material mat;

uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform vec3 objClr;
uniform vec3 viewPos;

//outputs
out vec4 fragclr;

//functions
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	if(light.on)
	{
		vec3 lightDir = normalize(-light.dir);
		//diffuse
		float diff = max(dot(normal,lightDir),0.0);
		//specular
		vec3 reflectDir = reflect(-lightDir,normal);
		float spec = pow(max(dot(viewDir,reflectDir),0.0),mat.shininess);
	
		//result
		vec3 ambient = light.ambient * vec3(texture(mat.diffuse,texcoords));
		vec3 diffuse = light.diffuse * diff * vec3(texture(mat.diffuse,texcoords));
		vec3 specular = light.specular * spec * vec3(texture(mat.specular,texcoords));
	
		vec3 result = ambient + diffuse + specular;
		return result;
	}else{
		return light.ambient * vec3(texture(mat.diffuse,texcoords));
	}
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	if(light.on)
	{
		vec3 lightDir = normalize(light.pos - fragPos);
		//diffuse
		float diff = max(dot(normal,lightDir),0.0);
		//specular
		vec3 reflectDir = reflect(-lightDir,normal);
		float spec = pow(max(dot(reflectDir,viewDir),0.0),mat.shininess);

		//components
		vec3 ambient = light.ambient * vec3(texture(mat.diffuse,texcoords));
		vec3 diffuse = light.diffuse * diff * vec3(texture(mat.diffuse,texcoords));
		vec3 specular = light.specular * spec * vec3(texture(mat.specular,texcoords));

		//attenuation
		float d = length(light.pos - fragPos);
		float attenuation = 1.0/(light.Kc + light.Kl*d + light.Kq*d*d);

		//result
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
	
		vec3 result = ambient + diffuse + specular;
		return result;
	}
	else{
		return light.ambient * vec3(texture(mat.diffuse,texcoords));
	}
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 result = vec3(0.0f);

	vec3 lightDir = normalize(light.pos - fragPos);

	if(light.on)
	{
		//diffuse
		float diff = max(dot(normal,lightDir),0.0);
		//specular
		vec3 reflectDir = reflect(-lightDir,normal);
		float spec = pow(max(dot(reflectDir,viewDir),0.0),mat.shininess);

		//components
		vec3 ambient = light.ambient * vec3(texture(mat.diffuse,texcoords));
		vec3 diffuse = light.diffuse * vec3(texture(mat.diffuse,texcoords)) * diff;
		vec3 specular = light.specular * vec3(texture(mat.specular,texcoords)) * spec;

		//intensity
		float theta = dot(lightDir,normalize(-light.dir));
		float epsilon = light.cutoff - light.outerCutoff;
		float intensity = clamp((theta - light.outerCutoff)/epsilon,0.0,1.0);

		//attenuation
		float d = length(light.pos - fragPos);
		float attenuation = 1.0/(light.Kc + light.Kq*d + light.Kq*d*d);

		//result
		ambient *= attenuation * intensity;
		diffuse *= attenuation * intensity;
		specular *= attenuation * intensity;

		result = ambient + diffuse + specular;
	}
	else{
		vec3 ambient = light.ambient * vec3(texture(mat.diffuse,texcoords));
		result = ambient;
	}

	
	return result;
}

//main
void main()
{
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - fragPos);

	vec3 result = vec3(0.0f);

	result += CalcDirLight(dirLight,norm,viewDir);

	result += CalcPointLight(pointLight,norm,fragPos,viewDir);

	result += CalcSpotLight(spotLight,norm,fragPos,viewDir);

	fragclr = vec4(result,1.0f);
}
