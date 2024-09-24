#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<uint32_t> indices, map<std::string, std::shared_ptr<Texture>> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
}

