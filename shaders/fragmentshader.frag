#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
     vec4 texColor = texture(texture_diffuse1, TexCoords);
    if(texColor.a < 0.1)
        FragColor = vec4(1,0,0,1); // Red for missing texture
    else
        FragColor = texColor;
}