#version 330 core

in vec3 vertexclr;

out vec4 fragclr;

void main()
{
	fragclr = vec4(vertexclr,1.0f);
}