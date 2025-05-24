#version 330 core

layout(location = 0) in vec3 pos;

uniform mat4 lightModel;
uniform mat4 lightView;
uniform mat4 lightProj;

void main()
{
	gl_Position = lightProj * lightView * lightModel * vec4(pos,1.0f);
}