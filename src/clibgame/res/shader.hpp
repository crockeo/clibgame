// Name: clibgame/res/shader.hpp
//
// Description:
//   A module to deal with loading and interacting with shaders.

#ifndef _CLIBGAME_RES_SHADER_HPP_
#define _CLIBGAME_RES_SHADER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <string>

//////////
// Code //

namespace clibgame {
    // Loading a specific type of shader.
    GLuint loadShader(std::string, GLenum) throw(std::runtime_error);

    // The shader program class.
    class Shader {
    private:
        bool original;
        GLuint id;

    public:
        // Loading a shader from a location on disk.
        Shader(std::string) throw(std::runtime_error);

        // Copying this shader.
        Shader(const Shader&);

        // Destroying this shader.
        ~Shader();

        // Getting the ID of this shader.
        GLuint getShaderID();
    };
}

#endif
