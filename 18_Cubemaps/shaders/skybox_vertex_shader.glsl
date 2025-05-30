#version 460 core
layout (location = 0) in vec3 aPos;

out vec3 vTexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    vTexCoords = aPos;
    vec4 position = projection * view * vec4(aPos, 1.0f);
    gl_Position = position.xyww;
}
