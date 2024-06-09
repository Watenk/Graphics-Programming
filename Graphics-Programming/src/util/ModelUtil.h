#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <assimp/scene.h>

#include "../Transform.h"
#include "../Mesh.h"
#include "../Shader.h"
#include "../Texture2D.h"
#include "../GameObject.h"

class ModelUtil{

public:
    static std::vector<GameObject*> loadModel(const int usage, const std::string path, Shader* shader, Camera* cam, float shininess);

private:
    static std::string directory;
    static std::vector<Texture2D*> loadedTextures; 
    static std::vector<GameObject*> models;
    
    static void processNode(const int usage, aiNode *node, const aiScene *scene, Shader* sahder, Camera* cam, float shininess);
    static GameObject* convertAIMeshToGameObject(const int usage, aiMesh *mesh, const aiScene *scene, Shader* sahder, Camera* cam, float shininess);
    static std::vector<Texture2D*> loadTexturesType(aiMaterial *aiMaterial, aiTextureType type);
};