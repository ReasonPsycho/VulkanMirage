#ifndef MESH_H
#define MESH_H

#include <map>
#include <memory>
#include <vector>
using namespace std;
#include "commonTypes/Texture.h"
#include "commonTypes/Vertex.h"

class Mesh {
public:
    // mesh Data
    vector<Vertex> vertices;
    vector<uint32_t> indices;
    map<std::string, std::shared_ptr<Texture>> textures;
    
    // constructor
    Mesh(vector<Vertex> vertices, vector<uint32_t> indices, map<std::string, std::shared_ptr<Texture>> textures);
};


#endif //MESH_H
