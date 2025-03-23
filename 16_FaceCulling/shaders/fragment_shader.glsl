#version 460 core

out vec4 FragColor;

in vec2 vTexCoords;

uniform sampler2D texture0;

void main()
{
    //FragColor = vec4(texture(texture0, vTexCoords).xyz, 1.0f);
    vec4 texColor = texture(texture0, vTexCoords);
    if (texColor.a < 0.1f)
        discard;
    FragColor = texColor;
}
