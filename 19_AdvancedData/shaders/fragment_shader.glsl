#version 460 core

out vec4 FragColor;

in vec3 vPos;
in vec3 vNormal;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
    float ratio = 1.0f/1.52f;
    vec3 cameraVector = normalize(vPos - cameraPos);
    //vec3 textureSampleLocation = normalize(reflect(cameraVector, vNormal));
    vec3 refractTexture = refract(cameraVector, normalize(vNormal), ratio);
    //use texture
    vec4 skyboxTexture = texture(skybox, refractTexture);
    //send to fragcolor
    FragColor = vec4(skyboxTexture.rgb, 1.0f);
}
