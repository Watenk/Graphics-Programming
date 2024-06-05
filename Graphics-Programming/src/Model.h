#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <assimp/scene.h>

#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture2D.h"

class Model{

public:
    std::vector<Mesh*> meshes;

    Model(const int usage, const std::string path, const Camera* cam);
    Model(std::vector<Mesh*> meshes);
    ~Model();

    void draw(Shader* shader) const;

private:
    std::string directory;
    std::vector<Texture2D*> loadedTextures; 
    
    void bind() const;
    void unBind() const;
    void processNode(const int usage, aiNode *node, const aiScene *scene, const Camera* cam);
    Mesh* convertAIMeshToMesh(const int usage, aiMesh *mesh, const aiScene *scene, const Camera* cam);
    std::vector<Texture2D*> loadTexturesType(aiMaterial *material, TextureType type);
};