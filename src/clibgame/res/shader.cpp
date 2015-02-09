#include "shader.hpp"

//////////////
// Includes //
#include <fstream>

//////////
// Code //

// Loading a specific type of shader.
GLuint clibgame::loadShader(std::string path, GLenum type) throw(std::runtime_error) {
    std::ifstream file(path);
    if (!file.good())
        throw std::runtime_error("Could not open file " + path + "!");

    std::string contents;
    while (!file.eof()) {
        if (file.peek() == -1)
            continue;
        contents.push_back((char)file.get());
    }

    GLuint shader = glCreateShader(type);
    if (shader == 0)
        throw std::runtime_error("Could not allocate shader.");

    const char* contentsCStr = contents.c_str();
    glShaderSource(shader, 1, &contentsCStr, nullptr);

    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        int len;
        GLchar log[1024];
        glGetShaderInfoLog(shader, 1024, &len, log);
        glDeleteShader(shader);

        throw std::runtime_error("Failed to compile shader '" + path + "': \n" + log + "\n");
    }

    return shader;
}
