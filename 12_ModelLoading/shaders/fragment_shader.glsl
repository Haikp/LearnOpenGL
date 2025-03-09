#version 460 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 orientationForward;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 vNormal;
in vec3 fragPos;
in vec2 vTexCoords;

uniform vec3 cameraPosition;
uniform Material material;
uniform DirLight dirLight;

#define NR_POINT_LIGHTS 1
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 fragPos, vec3 normal, vec3 viewDir);

void main()
{
    vec3 norm = normalize(vNormal);
    vec3 viewDir = normalize(cameraPosition - fragPos);
    vec3 fragResults = vec3(0.0f);

    fragResults += CalcDirLight(dirLight, norm, viewDir);

    for (int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        fragResults += CalcPointLight(pointLights[i], fragPos, norm, viewDir);
    }

    fragResults += CalcSpotLight(spotLight, fragPos, norm, viewDir);

    FragColor = vec4(fragResults, 1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    //ambient calc
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, vTexCoords));

    //diffuse calc
    vec3 lightVec = normalize(-light.direction);
    float diff = max(dot(lightVec, normal), 0.0);
    vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, vTexCoords)) * diff;

    //specular calc
    vec3 reflectedLightVec = reflect(-lightVec, normal);
    float spec = pow(max(dot(viewDir, reflectedLightVec), 0.0), material.shininess);
    vec3 specular = light.specular * vec3(texture(material.specular, vTexCoords)) * spec;

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 viewDir)
{
    //attentuation
    float distance = length(light.position - fragPos);
    float attentuation = 1 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    //ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, vTexCoords));
    //diffuse
    vec3 lightVec = normalize(light.position - fragPos);
    float diff = max(dot(lightVec, normal), 0.0);
    vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, vTexCoords)) * diff * attentuation;
    //specular
    vec3 reflectedLightVec = normalize(reflect(-lightVec, normal));
    float spec = pow(max(dot(reflectedLightVec, viewDir), 0.0), material.shininess);
    vec3 specular = light.specular * vec3(texture(material.specular, vTexCoords)) * spec * attentuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 fragPos, vec3 normal, vec3 viewDir)
{
    //ambient
    vec3 ambient = light.ambient * texture(material.diffuse, vTexCoords).rgb;

    //calculate the cut off values and their intensity
    //find the angle created between the fragment and the spotlight's light orientation
    vec3 spotLightForwardVec = normalize(light.orientationForward - light.position);
    vec3 currFragVec = normalize(fragPos - light.position);
    float theta = dot(spotLightForwardVec, currFragVec);

    //keep in mind we are working in cosine
    if(theta > light.outerCutOff)
    {
        //light fall off distance calculation
        float distance = length(light.position - fragPos);
        float attentuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

        //smooth edges on circle
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

        //diffuse
        vec3 lightVec = normalize(light.position - fragPos);
        float diff = max(dot(lightVec, normal), 0.0);
        vec3 diffuse = light.diffuse * texture(material.diffuse, vTexCoords).rgb * diff * intensity * attentuation;

        //specular
        vec3 reflectedLightVec = reflect(-lightVec, normal);
        float spec = pow(max(dot(viewDir, reflectedLightVec), 0.0), material.shininess);
        vec3 specular = light.specular * texture(material.specular, vTexCoords).rgb * spec * intensity * attentuation;

        return (ambient + diffuse + specular);
    }
    else
    {
        return ambient;
    }
}



























