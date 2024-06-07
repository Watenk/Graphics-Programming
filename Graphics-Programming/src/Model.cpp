#include "Model.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

Model::Model(const int usage, const std::string path, const Camera* cam){
    /* Read the model */
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_OptimizeMeshes);	
	
    /* Error check */
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    /* Process the meshes */
    processNode(usage, scene->mRootNode, scene, cam);
}

Model::Model(std::vector<Mesh*> meshes) : meshes(meshes) {}

Model::~Model(){
    for (Mesh* mesh : meshes){
        delete mesh;
    }
}

void Model::draw(Shader* shader) const{
    for (Mesh* mesh : meshes){
        mesh->draw(shader);
    }
}

void Model::processNode(const int usage, aiNode *node, const aiScene *scene, const Camera* cam){
    /* process all the node's meshes (if any) */ 
    for (unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(convertAIMeshToMesh(usage, mesh, scene, cam));			
    }

    /* then do the same for each of its children */ 
    for (unsigned int i = 0; i < node->mNumChildren; i++){
        processNode(usage, node->mChildren[i], scene, cam);
    }
}

Mesh* Model::convertAIMeshToMesh(const int usage, aiMesh *mesh, const aiScene *scene, const Camera* cam){
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture2D*> textures;

    /* Convert Vertices */
    for (unsigned int i = 0; i < mesh->mNumVertices; i++){

        /* Position */
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        /* Normal */
        vertices.push_back(mesh->mNormals[i].x);
        vertices.push_back(mesh->mNormals[i].y);
        vertices.push_back(mesh->mNormals[i].z);

        /* Texture cord */
        if(mesh->mTextureCoords[0]){ // if mesh contains texture coordinates
            vertices.push_back(mesh->mTextureCoords[0][i].x); 
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        }
        else{
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }
    }

    /* Convert Indices */
    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++) indices.push_back(face.mIndices[j]);
    }  

    /* Convert Materials */
    if(mesh->mMaterialIndex >= 0){ // if mesh contains a material
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        /* Diffuse Maps */
        std::vector<Texture2D*> diffuseMaps = loadTexturesType(material, TextureType::diffuse);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        /* Specular Maps */
        std::vector<Texture2D*> specularMaps = loadTexturesType(material, TextureType::specular);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }  

    return new Mesh(usage, vertices, indices, cam, textures);
}

std::vector<Texture2D*> Model::loadTexturesType(aiMaterial *material, TextureType type){

    /* Texture Type */
    aiTextureType aiType;
    switch (type){
    case TextureType::diffuse:
        aiType = aiTextureType_DIFFUSE;
        break;
    
    case TextureType::specular:
        aiType = aiTextureType_SPECULAR;
        break;
    }

    std::vector<Texture2D*> textures;
    for(unsigned int i = 0; i < material->GetTextureCount(aiType); i++){
        
        /* Get Texture Path */
        aiString textureName;
        material->GetTexture(aiType, i, &textureName);
        std::string path = std::string(directory + "/" + textureName.C_Str());

        /* Load Texture */
        /* Check if cached texture */
        bool skip = false;
        for(Texture2D* texture : loadedTextures){
            if(std::strcmp(texture->texturePath.c_str(), path.c_str()) == 0){
                textures.push_back(texture);
                skip = true; 
                break;
            }
        }

        /* Load Texture */
        if (!skip){
            Texture2D* newTexture = new Texture2D(path, type);
            textures.push_back(newTexture);
            loadedTextures.push_back(newTexture);
        }
    }
    return textures;
}