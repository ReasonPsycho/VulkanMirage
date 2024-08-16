//
// Created by redkc on 16/08/2024.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <stb_image.h>
#include <stdexcept>
#include <string>

/**
 * @brief The TextureData struct represents the data of a texture.
 *
 * It stores the pixel data, width, height, and the number of color channels.
 */
struct TextureData {
 /**
  * @brief Pointer to an array of unsigned characters.
  *
  * This variable is used to store an array of unsigned characters. It is typically used to represent binary data or raw pixel data.
  */
 unsigned char *data;
    /**
     * @brief The width of the texture.
     */
    int width, height, chanelsAmount;

 /**
  * @brief Creates TextureData object.
  *
  * This constructor is used to create a TextureData object with the given parameters.
  *
  * @param pData A pointer to the data array that contains the texture pixel data.
  * @param pWidth The width of the texture in pixels.
  * @param pHeight The height of the texture in pixels.
  * @param pChannelsAmount The number of color channels in the texture.
  */
 TextureData(unsigned char *pData, int pWidth, int pHeight, int pChanelsAmount)
        : data(pData), width(pWidth), height(pHeight), chanelsAmount(pChanelsAmount) {
    }

 /**
  * @brief Constructs a TextureData object from the given image file path.
  *
  * Loads the image file at the specified path using the stbi_load function from stb_image.h.
  * The loaded image data is stored in the TextureData object.
  *
  * @param path The file path of the image to load.
  *
  * @throws std::runtime_error If loading the image fails.
  */
 explicit TextureData(const std::string &path) {
        data = stbi_load(path.c_str(), &width, &height, &chanelsAmount, 0);
        if (!data) {
            throw std::runtime_error("failed load a texture!");
        }
    }   
};

/**
 * @struct Texture
 * @brief Represents a texture.
 */
struct Texture {
 /**
  * @struct TextureData
  * @brief Holds the data for a texture.
  *
  * TextureData consists of a pointer to the texture data, as well as the width,
  * height, and number of channels of the texture.
  */
 TextureData textureData;
 /**
  * @brief Represents a file path as a string.
  *
  * The path variable stores the file path as a string.
  */
 std::string path;

 /**
  * \class Texture
  * \brief Represents a texture.
  *
  * The Texture class is responsible for loading and storing texture data from a given file path.
  */
 Texture(const std::string &pPath)
        : path(pPath), textureData(pPath) {
    }
};



#endif //TEXTURE_H
