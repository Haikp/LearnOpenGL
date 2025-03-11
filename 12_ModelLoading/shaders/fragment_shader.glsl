#version 460 core

out vec4 FragColor;

in vec2 vTexCoords;

uniform sampler2D texture_diffuse0;

void main()
{
    FragColor = texture(texture_diffuse0, vTexCoords);
}
