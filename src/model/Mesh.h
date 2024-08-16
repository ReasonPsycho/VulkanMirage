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
    
    // constructor
    Mesh(vector<Vertex> vertices, vector<uint32_t> indices, map<std::string, std::shared_ptr<Texture>> textures);
};


#endif //MESH_H
