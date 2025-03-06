#version 460 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;

in vec3 vNormal;
in vec3 fragPos;
in vec2 vTexCoords;

uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;

void main()
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, vTexCoords));

    vec3 norm = normalize(vNormal);
    //vector from fragment pointing to light
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-(light.direction - light.position)));

    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);
    if (theta > light.outerCutOff)
    {
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
        //think of cosine on a unit circle to determine the value of the dot product, looking at the angle
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse = diff * light.diffuse * vec3(texture(material.diffuse, vTexCoords));

        vec3 viewDir = normalize(cameraPosition - fragPos);
        //vector from light source to fragment, reflected off the surface, creates a vector that points away from fragment
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        specular = spec * light.specular * vec3(texture(material.specular, vTexCoords));

        float distance = length(light.position - fragPos);
        float attentuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        diffuse *= attentuation;
        specular *= attentuation;
        diffuse *= intensity;
        specular *= intensity;
    }

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0f);
}
