#version 330 core

in vec3 vertexclr;
in vec2 texCoord;

uniform sampler2D Texture;
uniform sampler2D Texture2;

out vec4 fragclr;

void main()
{
	fragclr = mix(texture(Texture,texCoord), texture(Texture2,vec2(1-texCoord.x, texCoord.y)),0.2)*vec4(vertexclr,1.0);
}