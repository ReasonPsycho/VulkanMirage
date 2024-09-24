#ifndef MESH_H
#define MESH_H

#include <map>
#include <memory>
#include <vector>

#include "Texture.h"
#include "Vertex.h"
using namespace std;


class Mesh {
public:
    // mesh Data
    vector<Vertex> vertices;
    vector<uint32_t> indices;
    map<std::string, std::shared_ptr<Texture>> textures;

    // These are the handles you would get after buffering above geometry into GPU
    VkBuffer vertexBuffer;
    VkBuffer indexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkDeviceMemory indexBufferMemory;

    // Acceleration structure for BLAS - now stored directly in the Mesh struct.
    Mesh(vector<Vertex> vertices, vector<uint32_t> indices, map<std::string, std::shared_ptr<Texture>> textures);

};


#endif //MESH_H
