#version 460 core

out vec4 FragColor;
in vec2 vTexCoord;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float transparency;

void main()
{
    FragColor = mix(texture(tex0, vTexCoord), texture(tex1, vTexCoord), transparency);
}
