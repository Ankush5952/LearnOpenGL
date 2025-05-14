#version 330 core

layout(location=0) in vec3 aPos;
layout(location = 1) in vec3 clr;

uniform float offset;

out vec3 vertexclr;

void main()
{
	gl_Position = vec4(aPos.x+offset,aPos.yz,1.0);
	vertexclr = clr;
}