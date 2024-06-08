#version 330 core
out vec4 FragColor;

struct ExtraTextures{
    sampler2D extra0;
    sampler2D extra1;
    sampler2D extra2;
    sampler2D extra3;
    sampler2D extra4;
};

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

uniform vec3 viewPos;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform Material material;
uniform int activePointLights;
uniform int activeSpotLights;
uniform ExtraTextures extraTextures;

// Prototypes
void calcPhong(Phong phong, vec3 normal, vec3 viewDir, vec3 lightDirection, out vec3 ambientColor, out vec3 diffuseColor, out vec3 specularColor);
vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 lerp(vec3 a, vec3 b, float t);

void main(){
    // Normal 
    vec3 norm = texture(material.normal, texCoord).rgb;
    norm = normalize(norm * 2.0 - 1.0);
    norm.gb = norm.bg;
    norm.r = -norm.r;
    norm.b = -norm.b;

    vec3 viewDir = normalize(viewPos - fragPos);

    // Directional
    vec3 result = calcDirectionalLight(directionalLight, norm, viewDir);

    // Point
    //for(int i = 0; i < activePointLights; i++) result += calcPointLight(pointLights[i], norm, fragPos, viewDir);    
    
    // Spot
    // for(int i = 0; i < activeSpotLights; i++)
    //     result += calcSpotLight(spotLights[i], norm, fragPos, viewDir);    
    

    FragColor = texture(extraTextures.extra2, texCoord) * vec4(result, 1.0);
}

// This function calculates the phong light colors of: Ambient, Diffuse and specular
void calcPhong(Phong phong, vec3 normal, vec3 viewDir, vec3 lightDirection, out vec3 ambientColor, out vec3 diffuseColor, out vec3 specularColor){
    // Ambient
    ambientColor = phong.ambient * vec3(texture(material.diffuse, texCoord)); // Read texture uv and multiply it with light.ambientStrenght
    
    // Diffuse
    // float diffuseIntensity = max(dot(normal, lightDirection), 0.0); // Calc the angle (dot product) of the normal and the lightDirection and cutting off negatives with max()
    // diffuseColor = phong.diffuse * diffuseIntensity * vec3(texture(material.diffuse, texCoord)); // Read texture uv and multiply it with light.diffuseStrenght and diffuseIntensity
    float ds = clamp((fragPos.y - 50) / 10, -1, 1) * 0.5 + 0.5;
    float sg = clamp((fragPos.y - 100) / 10, -1, 1) * 0.5 + 0.5;
    float gr = clamp((fragPos.y - 150) / 10, -1, 1) * 0.5 + 0.5;
    float rs = clamp((fragPos.y - 200) / 10, -1, 1) * 0.5 + 0.5;

    vec3 dirtColor = texture(extraTextures.extra0, texCoord * 10).rgb;
    vec3 sandColor = texture(extraTextures.extra1, texCoord * 10).rgb;
    vec3 grassColor = texture(extraTextures.extra2, texCoord * 10).rgb;
    vec3 stoneColor = texture(extraTextures.extra3, texCoord * 10).rgb;
    vec3 snowColor = texture(extraTextures.extra4, texCoord * 10).rgb;

    diffuseColor = lerp(lerp(lerp(lerp(dirtColor, sandColor, ds), grassColor, sg), stoneColor, gr), snowColor, rs);

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
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.attenuation.constant + light.attenuation.linear * distance + light.attenuation.quadratic * (distance * distance));    
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

vec3 lerp(vec3 a, vec3 b, float t){
    return a + (b - a) * t;
}