#version 460 core

out vec4 FragColor;

in vec3 vNormal;
in vec3 fragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    //think of cosine on a unit circle to determine the value of the dot product, looking at the angle
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0f);
}
