#version 330 core

layout(location=0) in vec3 aPos;
layout(location = 1) in vec3 clr;
layout(location = 2) in vec2 tCoord;

uniform float offset;

out vec3 vertexclr;
out vec2 texCoord;

void main()
{
	gl_Position = vec4(aPos.x+offset,aPos.yz,1.0);
	vertexclr = clr;
	texCoord = tCoord;
}