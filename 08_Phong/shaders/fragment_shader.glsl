#version 460 core

out vec4 FragColor;

in vec3 vNormal;
in vec3 fragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPosition;

void main()
{
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(vNormal);
    //vector from fragment pointing to light
    vec3 lightDir = normalize(lightPos - fragPos);
    //think of cosine on a unit circle to determine the value of the dot product, looking at the angle
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(cameraPosition - fragPos);
    //vector from light source to fragment, reflected off the surface, creates a vector that points away from fragment
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0f);
}
