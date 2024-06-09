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
vec3 normalizeRGB(vec3 rgb);

void main(){
    // Normal 
    vec3 normal = texture(material.normal, texCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    normal.gb = normal.bg;
    normal.r = -normal.r;

    vec3 viewDir = normalize(viewPos - fragPos);

    // Directional
    vec3 result = calcDirectionalLight(directionalLight, normal, viewDir);

    // Point
    for(int i = 0; i < activePointLights; i++) result += calcPointLight(pointLights[i], normal, fragPos, viewDir);    
    
    // Spot
    // for(int i = 0; i < activeSpotLights; i++) result += calcSpotLight(spotLights[i], norm, fragPos, viewDir);    

    FragColor = vec4(result, 1.0);
}

// This function calculates the phong light colors of: Ambient, Diffuse and specular
void calcPhong(Phong phong, vec3 normal, vec3 viewDir, vec3 lightDirection, out vec3 ambientColor, out vec3 diffuseColor, out vec3 specularColor){
    
    float ds = clamp((fragPos.y - 5) / 10, -1, 1) * 0.5f + 0.5f;
    float sg = clamp((fragPos.y - 10) / 10, -1, 1) * 0.5f + 0.5f;
    float gr = clamp((fragPos.y - 25) / 10, -1, 1) * 0.5f + 0.5f;
    float rs = clamp((fragPos.y - 40) / 10, -1, 1) * 0.5f + 0.5f;

    float dist = length(fragPos - viewPos);
    float uvLerp = clamp((dist - 50) / 30, -1, 1) * 0.5f + 0.5f;

    vec3 dirtColorClose = texture(extraTextures.extra0, texCoord * 100).rgb;
    vec3 sandColorClose = texture(extraTextures.extra1, texCoord * 100).rgb;
    vec3 grassColorClose = texture(extraTextures.extra2, texCoord * 100).rgb;
    vec3 rockColorClose = texture(extraTextures.extra3, texCoord * 100).rgb;
    vec3 snowColorClose = texture(extraTextures.extra4, texCoord * 100).rgb;

    vec3 dirtColorFar = texture(extraTextures.extra0, texCoord * 10).rgb;
    vec3 sandColorFar = texture(extraTextures.extra1, texCoord * 10).rgb;
    vec3 grassColorFar = texture(extraTextures.extra2, texCoord * 10).rgb;
    vec3 rockColorFar = texture(extraTextures.extra3, texCoord * 10).rgb;
    vec3 snowColorFar = texture(extraTextures.extra4, texCoord * 10).rgb;

    vec3 dirtColor = lerp(dirtColorClose, dirtColorFar, uvLerp);
    vec3 sandColor = lerp(sandColorClose, sandColorFar, uvLerp);
    vec3 grassColor = lerp(grassColorClose, grassColorFar, uvLerp);
    vec3 rockColor = lerp(rockColorClose, rockColorFar, uvLerp);
    vec3 snowColor = lerp(snowColorClose, snowColorFar, uvLerp);

    vec3 texturesColor = lerp(lerp(lerp(lerp(dirtColor, sandColor, ds), grassColor, sg), rockColor, gr), snowColor, rs);

    // Fog
    float fog = pow(clamp((dist - 50) / 200, 0, 1), 2);
    vec3 skyTopColor = normalizeRGB(vec3(68.0f, 118.0f, 189.0f));
	vec3 skyBottomColor = normalizeRGB(vec3(188.0f, 214.0f, 231.0f));
    vec3 fogColor = lerp(skyBottomColor, skyTopColor, max(viewDir.y, 0.0));

    // Ambient
    ambientColor = phong.ambient * texturesColor;

    // Diffuse
    float diffuseIntensity = max(dot(normal, lightDirection), 0.0); // Calc the angle (dot product) of the normal and the lightDirection and cutting off negatives with max()
    diffuseColor = phong.diffuse * diffuseIntensity * texturesColor;
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
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.attenuation.constant + light.attenuation.linear * distance + light.attenuation.quadratic * (distance * distance));    
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