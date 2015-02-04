// Name: clibgame/res/texture.hpp
//
// Description:
//   This is meant to contain information surrounding the creation and use of
//   textures.

#ifndef _CLIBGAME_RES_TEXTURE_
#define _CLIBGAME_RES_TEXTURE_

//////////////
// Includes //
#include <GL/glew.h>
#include <string>
#include <vector>

#include "texable.hpp"

//////////
// Code //

namespace clibgame {
    // A class to reapresent an OpenGL texture.
    class Texture : public clibgame::Texable {
    private:
        int width, height;
        bool original;
        GLuint id;

        // Cleaning up the texture.
        void destroy();

    public:
        // Loading a texture from the disk.
        Texture(std::string);

        // Copy constructor.
        Texture(const Texture&);

        // Assignment operator.
        Texture& operator=(const Texture&);

        // Some accessors.
        int getWidth()                          const;
        int getHeight()                         const;
        bool isOriginal()                       const;
        GLuint getTextureID()                   const;
        std::vector<GLfloat> getTextureCoords() const;

        // Binding this texture.
        void bind() const;
    };
}

#endif
