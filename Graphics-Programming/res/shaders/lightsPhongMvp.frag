#version 330 core
out vec4 FragColor;

struct Material{
    // Light Maps
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
}; 

struct Phong{
    vec3 ambientStrenght;
    vec3 diffuseStrenght;
    vec3 specularStrenght;
};

struct DirectionalLight{
    // Directional
    vec3 direction;
	
    Phong phong;
};

struct PointLight{
    // Point
    vec3 position;
    
    Phong phong;

    // Attenutation
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight{
    // Spot
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    Phong phong;

    // Attenutation
    float constant;
    float linear;
    float quadratic;
};

#define POINT_LIGHTS 4
#define SPOT_LIGHTS 4

in vec3 fragPos;
in vec2 texCoord;
in vec3 normal;

uniform vec3 viewPos;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[POINT_LIGHTS];
uniform SpotLight spotLights[SPOT_LIGHTS];
uniform Material material;

// Prototypes
void calcPhong(Phong phong, vec3 normal, vec3 viewDir, vec3 lightDirection, out vec3 ambientColor, out vec3 diffuseColor, out vec3 specularColor);
vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(){
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    // Directional
    vec3 result = calcDirectionalLight(directionalLight, norm, viewDir);

    // Point
    for(int i = 0; i < POINT_LIGHTS; i++)
        result += calcPointLight(pointLights[i], norm, fragPos, viewDir);    
    
    // Spot
    for(int i = 0; i < SPOT_LIGHTS; i++)
        result += calcSpotLight(spotLights[i], norm, fragPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
}

// This function calculates the phong light colors of: Ambient, Diffuse and specular
void calcPhong(Phong phong, vec3 normal, vec3 viewDir, vec3 lightDirection, out vec3 ambientColor, out vec3 diffuseColor, out vec3 specularColor){
    // Ambient
    ambientColor = phong.ambientStrenght * vec3(texture(material.diffuse, texCoord)); // Read texture uv and multiply it with light.ambientStrenght
    
    // Diffuse
    float diffuseIntensity = max(dot(normal, lightDirection), 0.0); // Calc the angle (dot product) of the normal and the lightDirection and cutting off negatives with max()
    diffuseColor = phong.diffuseStrenght * diffuseIntensity * vec3(texture(material.diffuse, texCoord)); // Read texture uv and multiply it with light.diffuseStrenght and diffuseIntensity

    // Specular
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularIntensity = pow(max(dot(viewDir, reflectDirection), 0.0), material.shininess);
    specularColor = phong.specularStrenght * specularIntensity * vec3(texture(material.specular, texCoord)); // Read texture uv and multiply it with light.specularStrenght and diffuseIntensity
}

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir){
    vec3 lightDirection = normalize(-light.direction); // light.direction is negated so it points towards the light source

    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    calcPhong(light.phong, normal, viewDir, lightDirection, ambientColor, diffuseColor, specularColor);

    return (ambientColor + diffuseColor + specularColor);
}  

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDirection = normalize(light.position - fragPos);

    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    calcPhong(light.phong, normal, viewDir, lightDirection, ambientColor, diffuseColor, specularColor);

    // attenuation (light becomes less intense at a distance)
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    ambientColor *= attenuation;
    diffuseColor *= attenuation;
    specularColor *= attenuation;

    return (ambientColor + diffuseColor + specularColor);
} 

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDirection = normalize(light.position - fragPos);

    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    calcPhong(light.phong, normal, viewDir, lightDirection, ambientColor, diffuseColor, specularColor);

    

    return (ambientColor + diffuseColor + specularColor);
}