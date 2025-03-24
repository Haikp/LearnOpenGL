#version 460 core

out vec4 FragColor;

in vec2 vTexCoords;

uniform sampler2D texture0;

const float offsetX = 1.0f/1080.0f;
const float offsetY = 1.0f/720.0f;

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offsetX,  offsetY), // top-left
        vec2( 0.0f,    offsetY), // top-center
        vec2( offsetX,  offsetY), // top-right
        vec2(-offsetX,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offsetX,  0.0f),   // center-right
        vec2(-offsetX, -offsetY), // bottom-left
        vec2( 0.0f,   -offsetY), // bottom-center
        vec2( offsetX, -offsetY)  // bottom-right
    );

    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );

    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(texture0, vTexCoords + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
    {
        col += sampleTex[i] * kernel[i];
    }

    FragColor = vec4(col, 1.0);
}
