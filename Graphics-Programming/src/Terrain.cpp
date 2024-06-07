#include "Terrain.h"

#include <glm/glm.hpp>
#include <vector>
#include <iostream>

Terrain::Terrain(Texture2D* heightmap, Camera* cam, float heightScale, float xzScale) : heightmap(heightmap){
    
    int verticesAmount = heightmap->width * heightmap->height;
    int indicesAmount = (heightmap->width - 1) * (heightmap->height - 1);

    std::cout << "Loading Terrain of size (" << heightmap->width << ", " << heightmap->height << ")" << " with texture " << heightmap->texturePath << " and " << heightmap->channels << " channel(s)." << std::endl;

    /* Vertices */
    std::vector<float> vertices;
    for (int i = 0; i < verticesAmount; i++){

        /* Position */
        float x = static_cast<float>(i % heightmap->width);
        float y = static_cast<float>(heightmap->data[i * heightmap->channels]);
        float z = static_cast<float>(i / heightmap->width);

        vertices.push_back(x * xzScale); 
        vertices.push_back(y / 255.0f * heightScale);
        vertices.push_back(z * xzScale);

        /* Normals */
        vertices.push_back(0.0f); 
        vertices.push_back(1.0f); 
        vertices.push_back(0.0f); 

        /* Texture Coords */
        vertices.push_back(x / (static_cast<float>(heightmap->width) * xzScale)); 
        vertices.push_back(z / (static_cast<float>(heightmap->height) * xzScale)); 
    }

    /* Indices */
    std::vector<unsigned int> indices;
    for (int i = 0; i < indicesAmount; i++){
        /* Calc Position */
        unsigned int ix = static_cast<unsigned int>(i % (heightmap->width - 1));
        unsigned int iz = static_cast<unsigned int>(i / (heightmap->width - 1));

        /* Get the assosiated vertex */
        unsigned int vertex = iz * static_cast<unsigned int>(heightmap->width) + ix;

        /* Counterclockwise
        V----<----V+1
        | \       |
        v    >    ^
        |       \ |
        V+W-->--V+W+1
        */

       /* First Triangle */
        indices.push_back(vertex);
        indices.push_back(vertex + static_cast<unsigned int>(heightmap->width));
        indices.push_back(vertex + static_cast<unsigned int>(heightmap->width) + 1);

        /* Second Triangle */
        indices.push_back(vertex);
        indices.push_back(vertex + static_cast<unsigned int>(heightmap->width) + 1);
        indices.push_back(vertex + 1);
    }

    Texture2D* heightmapSpecular = new Texture2D("res/textures/heightmap.png", TextureType::specular);
    std::vector<Texture2D*> textures;
    textures.push_back(heightmap);
    textures.push_back(heightmapSpecular);

    std::cout << "Generated terrain with " << vertices.size() / 8 << " vertices and " << indices.size() / 6 << " indices" << std::endl;
    mesh = new Mesh(GL_STATIC_DRAW, vertices, indices, cam, textures);
}