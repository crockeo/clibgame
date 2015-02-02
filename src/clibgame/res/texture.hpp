#pragma once

//////////////
// Includes //
#include <GL/glew.h>
#include <vector>

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
    };
}
