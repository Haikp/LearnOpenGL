#version 460 core

out vec4 FragColor;
in vec3 vColor;
in vec3 vPos;

void main()
{
   FragColor = vec4(vPos, 1.0f);
}
