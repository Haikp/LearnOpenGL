#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 vPos;
out vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vNormal = mat3(transpose(inverse(model))) * aNormal;
    vPos = vec3(model * vec4(aPos, 1.0f));
    gl_Position = projection * view * model * vec4(aPos.xyz, 1.0f);
}
