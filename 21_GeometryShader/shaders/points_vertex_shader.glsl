#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

out VS_OUT {
    vec3 color;
} vs_out;

uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 0.0f, 1.0f);
    vs_out.color = aColor;
}
