#version 460 core
out vec4 FragColor;

void main()
{
    if(gl_FragCoord.x < 540)
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    else
        FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
