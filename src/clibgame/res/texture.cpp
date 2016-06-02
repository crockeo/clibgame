#include "texture.hpp"

//////////////
// Includes //
#include <iostream>
#include <fstream>
#include <png.h>
#include <tuple>

#include <cstdlib>
#include <cstdio>

//////////
// Code //

// Some configs.
const static int PNG_HEADER_SIZE = 8;
const static auto BAD_RETURN = std::make_tuple(0, -1, -1);

// Loading the header from a PNG.
png_byte* loadHeader(FILE* fp) {
    png_byte* header = new png_byte[PNG_HEADER_SIZE];

    fread(header, 1, PNG_HEADER_SIZE, fp);
    if (png_sig_cmp(header, 0, PNG_HEADER_SIZE) != 0) {
        delete[] header;
        return nullptr;
    }

    return header;
}

// Loading a PNG from a location on the disk.
std::tuple<GLuint, int, int> loadPNG(std::string path) {
    FILE* fp = fopen(path.c_str(), "rb");
    if (fp == nullptr) {
        std::cerr << "Failed to open file " << path << "!" << std::endl;
        fclose(fp);
        return BAD_RETURN;
    }

    // Loading the header.
    png_byte* header = loadHeader(fp);
    if (header == nullptr) {
        std::cerr << path << " is not a PNG!" << std::endl;
        fclose(fp);
        return BAD_RETURN;
    }

    delete[] header;

    // Loading the PNG thingy.
    png_structp pngPtr = png_create_read_struct(
        PNG_LIBPNG_VER_STRING,
        nullptr,
        nullptr,
        nullptr
    );

    if (pngPtr == nullptr) {
        std::cerr << "png_create_read_struct returned 0." << std::endl;
        fclose(fp);
        return BAD_RETURN;
    }

    // Loading the PNG info thingies.
    png_infop infoPtr = png_create_info_struct(pngPtr);
    if (infoPtr == nullptr) {
        std::cerr << "On infoPtr: png_create_info_struct returned nullptr." << std::endl;
        fclose(fp);
        return BAD_RETURN;
    }

    png_infop endInfoPtr = png_create_info_struct(pngPtr);
    if (endInfoPtr == nullptr) {
        std::cerr << "On endInfoPtr: png_create_info_struct returned nullptr." << std::endl;
        fclose(fp);
        return BAD_RETURN;
    }

    // Setting up libpng error handling.
    if (setjmp(png_jmpbuf(pngPtr))) {
        std::cerr << "libpng error!" << std::endl;
        png_destroy_read_struct(&pngPtr, &infoPtr, &endInfoPtr);
        fclose(fp);
        return BAD_RETURN;
    }

    // Initializing libpng.
    png_init_io(pngPtr, fp);
    png_set_sig_bytes(pngPtr, PNG_HEADER_SIZE);

    // Getting all the infos.
    int bitDepth, colorType;
    png_uint_32 width, height;

    png_read_info(pngPtr, infoPtr);
    png_get_IHDR(
        pngPtr,
        infoPtr,
        &width,
        &height,
        &bitDepth,
        &colorType,
        nullptr,
        nullptr,
        nullptr
    );

    // Getting the new infos?
    png_read_update_info(pngPtr, infoPtr);

    // Allocating image data.
    int rowBytes = png_get_rowbytes(pngPtr, infoPtr);
    png_byte* imageData = nullptr;
    png_bytep* rowPointers = nullptr;

    try {
        imageData = new png_byte[rowBytes * height];
        rowPointers = new png_bytep[height];
    } catch (const std::bad_alloc& err) {
        std::cerr << "Failed to alloc PNG data." << std::endl;
        png_destroy_read_struct(&pngPtr, &infoPtr, &endInfoPtr);
        fclose(fp);

        if (imageData != nullptr)
            delete[] imageData;
        if (rowPointers != nullptr)
            delete[] rowPointers;

        return BAD_RETURN;
    }

    // Reading the rows.
    for (int i = 0; i < height; i++)
        rowPointers[height - 1 - i] = imageData + i * rowBytes;
    png_read_image(pngPtr, rowPointers);

    // Setting the color type.
    GLenum glColorType;
    switch (colorType) {
    case PNG_COLOR_TYPE_RGB_ALPHA:
        glColorType = GL_RGBA;
        break;
    default:
        glColorType = GL_RGB;
        break;
    }

    // Generating the texture.
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, glColorType, width, height, 0, glColorType, GL_UNSIGNED_BYTE, imageData);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Cleaning up and returning.
    png_destroy_read_struct(&pngPtr, &infoPtr, &endInfoPtr);
    delete[] imageData;
    delete[] rowPointers;
    fclose(fp);
    return texture;
}

namespace clibgame {
    namespace res {
        // Loading a texture from the filesystem.
        Texture Texture::load(std::string path) throw(std::runtime_error) {
            Texture t;

            auto png = loadPNG(path);
            if (png == BAD_RETURN)
                throw std::runtime_error("Failed to load PNG from '" + path + "'!");

            t.id     = std::get<0>(png);
            t.width  = std::get<1>(png);
            t.height = std::get<2>(png);

            return t;
        }
    }
}
