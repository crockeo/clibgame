#ifndef _CLIBGAME_RES_TEXTURE_
#define _CLIBGAME_RES_TEXTURE_

//////////////
// Includes //
#include <GL/glew.h>
#include <string>

//////////
// Code //

namespace clibgame {
    // A class to represent an OpenGL texture.
    class Texture {
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
        int getWidth()    const;
        int getHeight()   const;
        bool isOriginal() const;
        GLuint getID()    const;

        // Binding this texture.
        void bind() const;
    };
}

#endif
