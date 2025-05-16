#version 330 core

layout(location=0) in vec3 aPos;
layout(location = 1) in vec2 tCoord;

uniform float offset;
uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 vertexclr;
out vec2 texCoord;

void main()
{
	gl_Position = proj * view * model * vec4(aPos.x+offset,aPos.yz,1.0);
	texCoord = tCoord;
}