#version 330 core

uniform vec3 objClr;
uniform vec3 lightClr;

out vec4 fragclr;

void main()
{
	fragclr = vec4(objClr*lightClr, 1.0f);
}