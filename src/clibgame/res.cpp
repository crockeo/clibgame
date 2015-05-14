#include "res.hpp"

//////////////
// Includes //
#include <parsical.hpp>
#include <cstring>
#include <fstream>

//////////
// Code //

// Creating an empty Res.
clibgame::Res::Res() { }

// Adding a set of resources.
void clibgame::Res::addAnimation(std::string name, std::string path, int cols, int rows, float frameLength, bool loops, int beginFrame, int endFrame) throw(std::runtime_error) {
    this->animations.emplace(std::piecewise_construct,
                             std::forward_as_tuple(name),
                             std::forward_as_tuple(path, cols, rows, frameLength, loops, beginFrame, endFrame));
}

// Adding a set of resources.
void clibgame::Res::addAnimation(std::string name, std::string path, int cols, int rows, float frameLength, bool loops) throw(std::runtime_error) {
    this->animations.emplace(std::piecewise_construct,
                             std::forward_as_tuple(name),
                             std::forward_as_tuple(path, cols, rows, frameLength, loops));
}

void clibgame::Res::addAnimation(std::string name, std::string path, int cols, int rows, float frameLength) throw(std::runtime_error) {
    this->addAnimation(name, path, cols, rows, frameLength, true);
}

void clibgame::Res::addTexSheet(std::string name, std::string path, int cols, int rows) throw(std::runtime_error) {
    this->texSheets.emplace(std::piecewise_construct,
                            std::forward_as_tuple(name),
                            std::forward_as_tuple(path, cols, rows));
}

void clibgame::Res::addTexture(std::string name, std::string path) throw(std::runtime_error) {
    this->textures.emplace(std::piecewise_construct,
                           std::forward_as_tuple(name),
                           std::forward_as_tuple(path));
}

void clibgame::Res::addShader(std::string name, std::string path) throw(std::runtime_error) {
    this->shaders.emplace(std::piecewise_construct,
                          std::forward_as_tuple(name),
                          std::forward_as_tuple(path));
}

void clibgame::Res::addFont(std::string name, std::string path, int pnt) throw(std::runtime_error) {
    this->fonts.emplace(std::piecewise_construct,
                        std::forward_as_tuple(name),
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
    using namespace parsical::str;

    parsical::IStreamParser p(stream);
    std::string prefix, name, path;

    while (!p.eof()) {
        try {
            consumeWhitespace(p);
            prefix = parseString(p);
            consumeWhitespace(p);
            
            name = parseString(p);
            consumeWhitespace(p);

            path = parseString(p);
            consumeWhitespace(p);

            if (prefix == "animation_f" || prefix == "animation") {
                int cols = parseInt(p);
                consumeWhitespace(p);

                int rows = parseInt(p);
                consumeWhitespace(p);

                float frameLength = parseFloat(p);
                consumeWhitespace(p);

                bool loops = parseBool(p);
                consumeWhitespace(p);

                if (prefix == "animation")
                    res.addAnimation(name, path, cols, rows, frameLength, loops);
                else {
                    int beginFrame = parseInt(p);
                    consumeWhitespace(p);

                    int endFrame = parseInt(p);
                    consumeWhitespace(p);

                    res.addAnimation(name, path, cols, rows, frameLength, loops, beginFrame, endFrame);
                }
            } else if (prefix.compare("texsheet") == 0) {
                int rows = parseInt(p);
                consumeWhitespace(p);

                int cols = parseInt(p);
                consumeWhitespace(p);

                res.addTexSheet(name, path, cols, rows);
            } else if (prefix.compare("texture") == 0) {
                res.addTexture(name, path);
            } else if (prefix.compare("shader") == 0) {
                res.addShader(name, path);
            } else if (prefix.compare("font") == 0) {
                int pnt = parseInt(p);
                consumeWhitespace(p);

                res.addFont(name, path, pnt);
            }
        } catch (parsical::ParseError& e) {
            throw std::runtime_error(("Failed to load assets: " + std::string(e.what())).c_str());
        }
    }
}

// Loading a set of resources from a file.
void clibgame::loadRes(Res& res, std::string path) throw(std::runtime_error) {
    std::ifstream file(path);
    clibgame::loadRes(res, file);
}
