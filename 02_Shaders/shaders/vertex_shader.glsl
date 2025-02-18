#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vColor;
out vec3 vPos;

uniform float offset;

void main()
{
    gl_Position = vec4(aPos.x + offset, aPos.yz, 1.0f);
    vColor = aColor;
    vPos = aPos;
}
