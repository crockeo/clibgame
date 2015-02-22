// Name: clibgame/res/texsheet.hpp
//
// Description:
//   This file provides a class to function as a spritesheet.

#ifndef _CLIBGAME_RES_TEXSHEET_HPP_
#define _CLIBGAME_RES_TEXSHEET_HPP_

//////////////
// Includes //
#include "texable.hpp"
#include "texture.hpp"

//////////
// Code //

namespace clibgame {
    // A class to represent a set of textures from a single image.
    class TexSheet : public clibgame::Texable {
    private:
        Texture texture;
        int cols, rows;
        int col, row;

    public:
        // Constructing a TexSheet from a given image with a given number of
        // columns and rows.
        TexSheet(std::string, int, int) throw(std::runtime_error);

        // Setting the position of the TexSheet.
        void setPosition(int, int);

        // Some accessors.
        int getColumns() const;
        int getRows() const;
        int getCurrentColumn() const;
        int getCurrentRow() const;

        // Getting the texture coords of the TexSheet as though the internal
        // column and row numbers were the ones provided.
        std::vector<GLfloat> getTextureCoordsAt(int, int) const;

        // Texable
        GLuint getTextureID() const;
        std::vector<GLfloat> getTextureCoords() const;
    };
}

#endif
