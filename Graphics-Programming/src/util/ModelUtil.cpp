#include "ModelUtil.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

std::string ModelUtil::directory;
std::vector<Texture2D*> ModelUtil::loadedTextures;
std::vector<GameObject*> ModelUtil::models;

std::vector<GameObject*> ModelUtil::loadModel(const int usage, const std::string path, Shader* shader, Camera* cam){
    /* Read the model */
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_OptimizeMeshes);	
	
    /* Error check */
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
    }
    directory = path.substr(0, path.find_last_of('/'));

    /* Process the meshes */
    processNode(usage, scene->mRootNode, scene, shader, cam);
    
    return models;
}

void ModelUtil::processNode(const int usage, aiNode *node, const aiScene *scene, Shader* shader, Camera* cam){
    /* process all the node's meshes (if any) */ 
    for (unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        models.push_back(convertAIMeshToGameObject(usage, mesh, scene, shader, cam));			
    }

    /* then do the same for each of its children */ 
    for (unsigned int i = 0; i < node->mNumChildren; i++){
        processNode(usage, node->mChildren[i], scene, shader, cam);
    }
}

GameObject* ModelUtil::convertAIMeshToGameObject(const int usage, aiMesh *aiMesh, const aiScene *scene, Shader* shader, Camera* cam){

    /* Convert Vertices */
    std::vector<float> vertices;
    for (unsigned int i = 0; i < aiMesh->mNumVertices; i++){

        /* Position */
        vertices.push_back(aiMesh->mVertices[i].x);
        vertices.push_back(aiMesh->mVertices[i].y);
        vertices.push_back(aiMesh->mVertices[i].z);

        /* Normal */
        vertices.push_back(aiMesh->mNormals[i].x);
        vertices.push_back(aiMesh->mNormals[i].y);
        vertices.push_back(aiMesh->mNormals[i].z);

        /* Texture cord */
        if(aiMesh->mTextureCoords[0]){ // if mesh contains texture coordinates
            vertices.push_back(aiMesh->mTextureCoords[0][i].x); 
            vertices.push_back(aiMesh->mTextureCoords[0][i].y);
        }
        else{
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }
    }

    /* Convert Indices */
    std::vector<unsigned int> indices;
    for(unsigned int i = 0; i < aiMesh->mNumFaces; i++){
        aiFace face = aiMesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++) indices.push_back(face.mIndices[j]);
    }  

    /* Convert Materials */
    std::vector<Texture2D*> textures;
    Material* material = new Material();
    if(aiMesh->mMaterialIndex >= 0){ // if mesh contains a material
        aiMaterial *aiMaterial = scene->mMaterials[aiMesh->mMaterialIndex];

        /* Diffuse Maps */
        std::vector<Texture2D*> diffuseMaps = loadTexturesType(aiMaterial, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        material->diffuseTexture = textures[0];

        /* Specular Maps */
        std::vector<Texture2D*> specularMaps = loadTexturesType(aiMaterial, aiTextureType_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        material->specularTexture = textures[1];
    }  

    Mesh* mesh = new Mesh(usage, vertices, indices);
    return new GameObject(mesh, shader, material, cam);
}

std::vector<Texture2D*> ModelUtil::loadTexturesType(aiMaterial *material, aiTextureType type){

    std::vector<Texture2D*> textures;
    for(unsigned int i = 0; i < material->GetTextureCount(type); i++){
        
        /* Get Texture Path */
        aiString textureName;
        material->GetTexture(type, i, &textureName);
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