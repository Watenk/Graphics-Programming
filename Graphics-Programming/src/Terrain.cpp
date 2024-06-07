#include "Terrain.h"

#include <glm/glm.hpp>
#include <vector>
#include <iostream>

Terrain::Terrain(Texture2D* heightmap, Camera* cam, float heightScale, float xzScale) : heightmap(heightmap){
    
    int verticesAmount = heightmap->width * heightmap->height;
    int indicesAmount = (heightmap->width - 1) * (heightmap->height - 1);

    std::cout << "Loading Terrain of size (" << heightmap->width << ", " << heightmap->height << ")" << std::endl;

    /* Vertices */
    std::vector<float> vertices;
    for (int i = 0; i < verticesAmount; i++){

        /* Position */
        int x = i % heightmap->width;
        int z = i / heightmap->width;
        float y = (float)heightmap->data[(z * heightmap->width + x) * heightmap->channels];

        vertices.push_back(x * xzScale); 
        vertices.push_back((y / 255.0f) * heightScale);
        vertices.push_back(z * xzScale);

        /* Normals */
        vertices.push_back(0); 
        vertices.push_back(1); 
        vertices.push_back(0); 

        /* Texture Coords */
        vertices.push_back((float)x / (heightmap->width * xzScale)); 
        vertices.push_back((float)z / (heightmap->height * xzScale)); 
    }

    /* Indices */
    std::vector<unsigned int> indices;
    for (int i = 0; i < indicesAmount; i++){
        /* Calc Position */
        int x = i % (heightmap->width - 1);
        int z = i / (heightmap->width - 1);

        /* Get the assosiated vertex */
        int vertex = z * heightmap->width + x;

        /* Counterclockwise
        V----<----V+1
        | \       |
        v    >    ^
        |       \ |
        V+W-->--V+W+1
        */

       /* First Triangle */
        indices.push_back(vertex);
        indices.push_back(vertex + heightmap->width);
        indices.push_back(vertex + heightmap->width + 1);

        /* Second Triangle */
        indices.push_back(vertex);
        indices.push_back(vertex + heightmap->width + 1);
        indices.push_back(vertex + 1);
    }

    std::vector<Texture2D*> textures;
    textures.push_back(heightmap);

    mesh = new Mesh(GL_STATIC_DRAW, vertices, indices, cam, textures);
}