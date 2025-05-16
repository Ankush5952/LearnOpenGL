#version 330 core

in vec2 texCoord;

uniform sampler2D Texture;
uniform sampler2D Texture2;

out vec4 fragclr;

void main()
{
	fragclr = mix(texture(Texture,texCoord), texture(Texture2,vec2(texCoord.x, texCoord.y)),0.3);
}