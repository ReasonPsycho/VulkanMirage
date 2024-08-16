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

    /**
     
     \class Model
     
     \brief Represents a 3D model.
     
     The Model class is responsible for loading and storing a 3D model from a given file path. It uses the ASSIMP library to read model files.
     
     \var vector<shared_ptr<Texture>> Model::textures_loaded
     
     \brief A vector of loaded textures.
     
     The textures_loaded vector stores shared_ptr objects that point to loaded textures. Each texture is represented by a Texture object.
     
     \var vector<unique_ptr<Mesh>> Model::meshes
     
     \brief A vector of meshes.
     
     The meshes vector stores unique_ptr objects that point to Mesh objects. Each Mesh object represents a mesh of the model.
     
     \var string Model::directory
     
     \brief The directory path of the model file.
     
     The directory variable stores the directory path of the model file. This path is used to resolve relative paths of textures used by the model.
     
     \param path The file path of the model.
     \param gamma A flag indicating whether gamma correction should be applied to the loaded textures.
     
     \fn void Model::loadModel(string const &path)
     
     \brief Loads the model from the given file.
     
     The loadModel function reads the model file using the ASSIMP library. It checks for errors and retrieves the directory path of the file. Then, it recursively processes the root node of the model.
     
     \param path The file path of the model.
     
     \fn void Model::processNode(aiNode *node, const aiScene *scene)
     
     \brief Processes a node of the model.
     
     The processNode function recursively processes a node of the model hierarchy. It processes each mesh in the node and processes its child nodes.
     
     \param node The node to process.
     \param scene The ASSIMP scene object.
     
     \fn unique_ptr<Mesh> Model::processMesh(aiMesh *mesh, const aiScene *scene)
     
     \brief Processes a mesh of the model.
     
     The processMesh function processes a mesh of the model. It creates a Mesh object and sets its data using the information from the mesh.
     
     \param mesh The mesh to process.
     \param scene The ASSIMP scene object.
     
     \fn shared_ptr<Texture> Model::loadMaterialTexture(aiMaterial *mat, aiTextureType type)
     
     \brief Loads a material texture.
     
     The loadMaterialTexture function loads a material texture from the given material and texture type. It returns a shared_ptr object that points to the loaded texture.
     
     \param mat The material.
     \param type The texture type.
     
     \struct Texture
     
     \brief Holds the data for a texture.
     
     The Texture structure consists of a pointer to the texture data, as well as the width, height, and number of channels of the texture.
     
     \var void* Texture::data
     
     \brief A pointer to the texture data.
     
     The data variable stores a pointer to the texture data. It can be used to access the raw texture data.
     
     \var int Texture::width
     
     \brief The width of the texture.
     
     The width variable stores the width of the texture in pixels.
     
     \var int Texture::height
     
     \brief The height of the texture.
     
     The height variable stores the height of the texture in pixels.
     
     \var int Texture::channels
     
     \brief The number of channels of the texture.
     
     The channels variable stores the number of channels of the texture. For example, 3 for RGB and 4 for RGBA.
     
     \class Mesh
     
     \brief Represents a mesh.
     
     The Mesh class is responsible for storing mesh data, such as vertex positions, normals, texture coordinates, and indices.
     
     \fn Mesh::Mesh()
     
     \brief Constructs a Mesh object.
     
     The constructor initializes the mesh data with default values.
     
     */
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
