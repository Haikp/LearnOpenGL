#version 460 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 vNormal;
in vec3 fragPos;

uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;

void main()
{
    vec3 ambient = material.ambient * light.ambient;

    vec3 norm = normalize(vNormal);
    //vector from fragment pointing to light
    vec3 lightDir = normalize(lightPos - fragPos);
    //think of cosine on a unit circle to determine the value of the dot product, looking at the angle
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * material.diffuse) * light.diffuse;

    vec3 viewDir = normalize(cameraPosition - fragPos);
    //vector from light source to fragment, reflected off the surface, creates a vector that points away from fragment
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * light.specular;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0f);
}
