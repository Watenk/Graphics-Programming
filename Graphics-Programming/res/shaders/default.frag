#version 330 core
out vec4 FragColor;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    float shininess;
}; 

struct Phong{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Attenutation{
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight{
    vec3 direction;
    Phong phong;
};

struct PointLight{
    vec3 position;
    vec3 color;
    Phong phong;
    Attenutation attenuation;
};

struct SpotLight{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    Phong phong;
    Attenutation attenuation;
};

#define MAX_POINT_LIGHTS 16
#define MAX_SPOT_LIGHTS 16

in vec3 fragPos;
in vec2 texCoord;
in vec3 normal;
in mat3 tbn;

uniform vec3 viewPos;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform Material material;
uniform int activePointLights;
uniform int activeSpotLights;

// Prototypes
void calcPhong(Phong phong, vec3 normal, vec3 viewDir, vec3 lightDirection, out vec3 ambientColor, out vec3 diffuseColor, out vec3 specularColor);
vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 lerp(vec3 a, vec3 b, float t);
vec3 normalizeRGB(vec3 rgb);

void main(){
    // Normal 
    vec3 norm = texture(material.normal, texCoord).rgb;
    norm = norm * 2.0 - 1.0;
    norm = normalize(tbn * norm);
    //vec3 norm = normal;

    vec3 viewDir = normalize(viewPos - fragPos);

    // Directional
    vec3 result = calcDirectionalLight(directionalLight, norm, viewDir);

    // Point
    for(int i = 0; i < activePointLights; i++) result += calcPointLight(pointLights[i], norm, fragPos, viewDir);    
    
    // Spot
    // for(int i = 0; i < activeSpotLights; i++) result += calcSpotLight(spotLights[i], norm, fragPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
}

// This function calculates the phong light colors of: Ambient, Diffuse and specular
void calcPhong(Phong phong, vec3 normal, vec3 viewDir, vec3 lightDirection, out vec3 ambientColor, out vec3 diffuseColor, out vec3 specularColor){
    // Ambient
    ambientColor = phong.ambient * vec3(texture(material.diffuse, texCoord)); // Read texture uv and multiply it with light.ambientStrenght
    
    // Fog
    float dist = length(fragPos - viewPos);
    float fog = pow(clamp((dist - 50) / 200, 0, 1), 2);
    vec3 skyTopColor = normalizeRGB(vec3(68.0f, 118.0f, 189.0f));
	vec3 skyBottomColor = normalizeRGB(vec3(188.0f, 214.0f, 231.0f));
    vec3 fogColor = lerp(skyBottomColor, skyTopColor, max(viewDir.y, 0.0));

    // Diffuse
    float diffuseIntensity = max(dot(normal, lightDirection), 0.0); // Calc the angle (dot product) of the normal and the lightDirection and cutting off negatives with max()
    diffuseColor = phong.diffuse * diffuseIntensity * vec3(texture(material.diffuse, texCoord)); // Read texture uv and multiply it with light.diffuseStrenght and diffuseIntensity
    diffuseColor = lerp(diffuseColor, fogColor, fog);

    // Specular
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularIntensity = pow(max(dot(viewDir, reflectDirection), 0.0), material.shininess);
    specularColor = phong.specular * specularIntensity * vec3(texture(material.specular, texCoord)); // Read texture uv and multiply it with light.specularStrenght and diffuseIntensity
}

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir){
    vec3 lightDirection = normalize(light.direction); // light.direction is negated so it points towards the light source

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
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.attenuation.constant + light.attenuation.linear * dist + light.attenuation.quadratic * (dist * dist));    
    ambientColor *= attenuation * light.color;
    diffuseColor *= attenuation * light.color;
    specularColor *= attenuation * light.color;

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

vec3 lerp(vec3 a, vec3 b, float t){
    return a + (b - a) * t;
}

vec3 normalizeRGB(vec3 rgb){
	return vec3(rgb.x / 255.0f, rgb.y / 255.0f, rgb.z / 255.0f);
}