#version 460 core

out vec4 FragColor;

in vec2 vTexCoords;

uniform sampler2D texture0;

void main()
{
    //FragColor = texture(texture0, vTexCoords);
    FragColor = vec4(texture(texture0, vTexCoords).xyz, 1.0f);
}
