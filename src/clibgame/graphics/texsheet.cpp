#include "texsheet.hpp"

//////////
// Code //

// Constructing a TexSheet from a given image with a given number of
// columns and rows.
clibgame::TexSheet::TexSheet(std::string path, int cols, int rows) throw(std::runtime_error)
        : texture(path) {
    this->cols = cols;
    this->rows = rows;
    
    this->col = 0;
    this->row = 0;
}

// Setting the position of the TexSheet.
void clibgame::TexSheet::setPosition(int col, int row) {
    this->col = col;
    this->row = row;
}

// Some accessors.
int clibgame::TexSheet::getColumns() const { return this->cols; }
int clibgame::TexSheet::getRows() const { return this->rows; }
int clibgame::TexSheet::getCurrentColumn() const { return this->col; }
int clibgame::TexSheet::getCurrentRow() const { return this->row; }

// Getting the texture coords of the TexSheet as though the internal
// column and row numbers were the ones provided.
std::vector<GLfloat> clibgame::TexSheet::getTextureCoordsAt(int col, int row) const {
    GLfloat x = col / static_cast<float>(this->cols),
            y = row / static_cast<float>(this->rows),
            w = 1   / static_cast<float>(this->cols),
            h = 1   / static_cast<float>(this->rows);

    std::vector<GLfloat> coords {
        x    , y    ,
        x + w, y    ,
        x + w, y + h,
        x    , y + h
    };

    return coords;
}

// Texable
GLuint clibgame::TexSheet::getTextureID() const {
    return this->texture.getTextureID();
}

std::vector<GLfloat> clibgame::TexSheet::getTextureCoords() const {
    return this->getTextureCoordsAt(this->col, this->row);
}
