// Name: clib/res/texable.hpp
//
// Description:
//   This file provides the abstract API for which a texturable class
//   can be based.

#ifndef _CLIBGAME_RES_TEXABLE_HPP_
#define _CLIBGAME_RES_TEXABLE_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <vector>

//////////
// Code //

namespace clibgame {
    // The abstract class.
    class Texable {
    public:
        // Getting the ID of this texture.
        virtual GLuint getTextureID() = 0;

        // Getting the desired texture coordinates to use with this texture.
        virtual std::vector<GLfloat> getTextureCoords() = 0;
    };
}

#endif
