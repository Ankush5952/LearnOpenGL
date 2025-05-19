#version 330 core

layout(location=0) in vec3 aPos;
layout(location  = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 fragPos;
out vec3 normal;

void main()
{
	fragPos = vec3(model * vec4(aPos,1.0f));
	gl_Position = proj * view * model * vec4(aPos,1.0);
	normal = aNormal * mat3(transpose(inverse(model))); //calculating inverse in shaders is costly, try to calculate it on CPU and send to shader as a uniform!
}