#include "res.hpp"

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
