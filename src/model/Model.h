//
// Created by redkc on 15/08/2024.
//

#ifndef MODEL_H
#define MODEL_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Mesh.h"
using namespace std;

/**
 * @brief A vector of shared pointers to Texture objects representing the loaded textures for the model.
 */
class Model {
    /**
     * @struct Texture
     * @brief Represents a texture.
     *
     * The Texture struct is responsible for storing information about a texture,
     * such as its file path and texture data.
     */
public:
    vector<shared_ptr<Texture> > textures_loaded;
    /**
     * @brief Represents a vector of unique pointers to Mesh objects.
     *
     * The meshes vector holds a collection of unique pointers to Mesh objects.
     * Each Mesh object represents a 3D mesh with its associated vertices, indices, and textures.
     *
     * The Mesh class is defined in the Mesh.h file and is used to create Mesh objects.
     *
     * Example usage:
     * @code
     * vector<unique_ptr<Mesh>> meshes;
     * @endcode
     */
    vector<unique_ptr<Mesh> > meshes;



    string directory;



    /**
     * @brief Initializes a new instance of the Model class.
     * @param path The path to the model file.
     */
    explicit Model(string const &path);

private:
    /**
     * Loads a 3D model from the specified file path.
     *
     * @param path The file path of the model to load.
     */
    void loadModel(string const &path);

    /**
     * Processes each node in the scene.
     * This function is called recursively to process each child node of the given node.
     *
     * @param node  Pointer to the current aiNode being processed.
     * @param scene Pointer to the aiScene containing the node and mesh data.
     */
    void processNode(aiNode *node, const aiScene *scene);

    /**
     * Process a mesh and extract its data.
     *
     * @param mesh The mesh to be processed.
     * @param scene The scene containing the mesh.
     * @return A unique pointer to a Mesh object created from the extracted mesh data.
     */
    unique_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);

    /**
     * @brief Load material texture.
     *
     * This method is responsible for loading a material texture from the given aiMaterial and aiTextureType.
     * If the texture has already been loaded, it will return the previously loaded texture for optimization.
     * If the texture has not been loaded yet, it will create a new Texture object and add it to the textures_loaded vector.
     *
     * @param mat The aiMaterial to load the texture from.
     * @param type The aiTextureType of the texture to load.
     * @return The loaded material texture as a shared_ptr<Texture>.
     * @note If the texture does not exist in the aiMaterial, it is handled by a TODO comment in the code.
     */
    // the required info is returned as a Texture struct.
    std::shared_ptr<Texture> loadMaterialTexture(aiMaterial *mat, aiTextureType type) {
        if (mat->GetTextureCount(type) > 0) {
            aiString str;
            mat->GetTexture(type, 0, &str);
            for (unsigned int j = 0; j < textures_loaded.size(); j++) {
                if (std::strcmp(textures_loaded[j].get()->path.data(), str.C_Str()) == 0) {
                    return textures_loaded[j];
                    // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
                auto texture = make_shared<Texture>(str.C_Str());
                textures_loaded.push_back(texture);
                return texture;
            }
        } else {
            throw std::runtime_error("failed to load texture!");
            //TODO handle not having this texture
        }
    }
};

#endif //MODEL_H
