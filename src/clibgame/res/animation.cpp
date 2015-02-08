#include "animation.hpp"

///////////
// Code //

// Getting the row and column of the current frame.
std::tuple<int, int> clibgame::Animation::getCurrentFrame() const {
    int index = this->timer.getTime() / this->frameLength;
    int col, row;

    row = index / this->texSheet.getColumns();
    col = index - this->texSheet.getColumns() * row;

    return std::make_tuple(col, row);
}

// Loading an Animation from the file system with an option of whether
// or not it should loop.
clibgame::Animation::Animation(std::string path, int cols, int rows, float frameLength, bool loop) :
        texSheet(path, cols, rows) {
    this->frameLength = frameLength;
    this->loop = loop;
    this->timer = Timer(loop ? -1 : frameLength * cols * rows);
}

// Loading an animation from the file system that will always loop.
clibgame::Animation::Animation(std::string path, int cols, int rows, float frameLength) :
        clibgame::Animation(path, cols, rows, frameLength, true) { }

// Creating an animation from a texture sheet with an option of whether
// or not it shoud loop.
clibgame::Animation::Animation(clibgame::TexSheet texSheet, float frameLength, bool loop) :
        texSheet(texSheet) {
    this->frameLength = frameLength;
    this->loop = loop;
    this->timer = Timer(loop ? -1 : frameLength * texSheet.getColumns() * texSheet.getRows());
}

// Creating an animation from a texture sheet that will always loop.
clibgame::Animation::Animation(clibgame::TexSheet texSheet, float frameLength) :
        clibgame::Animation(texSheet, frameLength, true) { }

// Getting the ID of the animation.
GLuint clibgame::Animation::getTextureID() const {
    return this->texSheet.getTextureID();
}

// Getting the texture coordinates of this thingy.
std::vector<GLfloat> clibgame::Animation::getTextureCoords() const {
    auto coords = this->getCurrentFrame();
    return this->texSheet.getTextureCoordsAt(std::get<0>(coords), std::get<1>(coords));
}
