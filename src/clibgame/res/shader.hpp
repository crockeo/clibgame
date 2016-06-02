// Name: clibgame/res/shader.hpp
//
// Description:
//   A module to deal with loading and interacting with shaders.

// Name     : clibgame/res/shader.hpp
// Author(s): Cerek Hillen
// Init Date: 2016-06-02
// Edit Date: 2016-06-02
//
// Description:
//   Utilities to load shaders and shader programs from the filesystem.

#ifndef _CLIBGAME_RES_SHADER_HPP_
#define _CLIBGAME_RES_SHADER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <string>

//////////
// Code //

namespace clibgame {
    namespace res {
        typedef GLuint Shader;
        typedef GLuint ShaderProgram;

        // Loading a single shader from the filesystem.
        Shader loadShader(std::string path, GLenum kind) throw(std::runtime_error, std::logic_error);

        // Linking a shader program from three Shaders (vertex, fragment, and
        // geometry).
        ShaderProgram linkShaderProgram(Shader vert, Shader frag, Shader geom) throw(std::runtime_error, std::logic_error);

        // Loading an entire shader program from the file system. Effectively
        // a nice combination of loadShader(...) and linkShaderProgram(...).
        ShaderProgram loadShaderProgram(std::string basePath) throw(std::runtime_error);
    }
}

#endif
