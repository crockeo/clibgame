#include "res.hpp"

//////////////
// Includes //
#include <fstream>

//////////
// Code //

// Creating an empty Res.
clibgame::Res::Res() { }

// Adding a set of resources.
void clibgame::Res::addAnimation(std::string path, int cols, int rows, float frameLength, bool loops) {
    this->animations.emplace(std::piecewise_construct,
                             std::forward_as_tuple(path),
                             std::forward_as_tuple(path, cols, rows, frameLength, loops));
}

void clibgame::Res::addAnimation(std::string path, int cols, int rows, float frameLength) {
    this->addAnimation(path, cols, rows, frameLength, true);
}

void clibgame::Res::addTexSheet(std::string path, int cols, int rows) {
    this->texSheets.emplace(std::piecewise_construct,
                            std::forward_as_tuple(path),
                            std::forward_as_tuple(path, cols, rows));
}

void clibgame::Res::addTexture(std::string path) {
    this->textures.emplace(std::piecewise_construct,
                           std::forward_as_tuple(path),
                           std::forward_as_tuple(path));
}

void clibgame::Res::addShader(std::string path) { 
    this->shaders.emplace(std::piecewise_construct,
                          std::forward_as_tuple(path),
                          std::forward_as_tuple(path));
}

void clibgame::Res::addFont(std::string path, int pnt) {
    this->fonts.emplace(std::piecewise_construct,
                        std::forward_as_tuple(path),
                        std::forward_as_tuple(path, pnt));
}

// Getting a set of resources.
clibgame::Animation clibgame::Res::getAnimation(std::string name) const {
    return this->animations.at(name);
}

clibgame::TexSheet clibgame::Res::getTexSheet(std::string name) const {
    return this->texSheets.at(name);
}

clibgame::Texture clibgame::Res::getTexture(std::string name) const {
    return this->textures.at(name);
}

clibgame::Shader clibgame::Res::getShader(std::string name) const {
    return this->shaders.at(name);
}

clibgame::Font clibgame::Res::getFont(std::string name) const {
    return this->fonts.at(name);
}

// Loading a set of resources from an std::istream.
void clibgame::loadRes(Res& res, std::istream& stream) throw (std::runtime_error) {
    if (!stream.good() || stream.eof())
        throw std::runtime_error("Stream is not good.");

    std::string prefix, path;
    while (!stream.eof()) {
        stream >> prefix;
        stream >> path;

        if (prefix.compare("animation") == 0) {
            int cols, rows;
            bool loops;

            stream >> cols;
            stream >> rows;
            stream >> loops;

            res.addAnimation(path, cols, rows, loops);
        } else if (prefix.compare("texsheet") == 0) {
            int cols, rows;
            stream >> cols;
            stream >> rows;

            res.addTexSheet(path, cols, rows);
        } else if (prefix.compare("texture") == 0) {
            res.addTexture(path);
        } else if (prefix.compare("shader") == 0) {
            res.addShader(path);
        } else if (prefix.compare("font") == 0) {
            int pnt;
            stream >> pnt;

            res.addFont(path, pnt);
        }
    }
}

// Loading a set of resources from a file.
void clibgame::loadRes(Res& res, std::string path) throw(std::runtime_error) {
    std::ifstream file(path);
    clibgame::loadRes(res, file);
}
