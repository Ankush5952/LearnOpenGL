#version 330 core

uniform vec3 lightClr;

out vec4 fragClr;

void main()
{
	fragClr = vec4(lightClr,1.0f);
}