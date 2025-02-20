#version 460 core

out vec4 FragColor;
in vec3 vColor;
in vec2 vTexCoord;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float transparency;

void main()
{
    vec2 newTexCoord = vTexCoord;
    newTexCoord.x = 1.0f - newTexCoord.x;
    FragColor = mix(texture(tex0, vTexCoord), texture(tex1, newTexCoord), transparency);
}
