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
}

#endif
