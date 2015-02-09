#include "shader.hpp"

//////////////
// Includes //
#include <iostream>
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

// Loading a shader from a location on disk.
clibgame::Shader::Shader(std::string path) throw(std::runtime_error) {
    auto tryLoadShader = [](std::string path, GLenum type) -> GLuint {
        GLuint n = 0;
        try { n = clibgame::loadShader(path, type); }
        catch (std::runtime_error& err) {
            std::cerr << err.what() << std::endl;
        }

        return n;
    };

    // Trying to load all of the shaders.
    GLuint vertShader = tryLoadShader(path + ".vert", GL_VERTEX_SHADER),
           fragShader = tryLoadShader(path + ".frag", GL_FRAGMENT_SHADER),
           geomShader = tryLoadShader(path + ".geom", GL_GEOMETRY_SHADER);

    if (vertShader == 0 && fragShader == 0 && geomShader == 0)
        throw std::runtime_error("No shaders were loaded.");
    else {
        this->id = glCreateProgram();

        if (vertShader != 0) glAttachShader(id, vertShader);
        if (fragShader != 0) glAttachShader(id, fragShader);
        if (geomShader != 0) glAttachShader(id, geomShader);

        glLinkProgram(this->id);

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
        glDeleteShader(geomShader);

        int linked;
        glGetProgramiv(this->id, GL_LINK_STATUS, &linked);
        if (linked == GL_FALSE) {
            glDeleteProgram(this->id);
            throw std::runtime_error("Failed to link shader program.");
        }

        this->original = true;
    }
}


// Copying this shader.
clibgame::Shader::Shader(const Shader& shader) {
    this->original = false;
    this->id       = shader.id;
}

// Destroying this shader.
clibgame::Shader::~Shader() {
    if (this->original)
        glDeleteProgram(this->id);
}

// Getting the ID of this shader.
GLuint clibgame::Shader::getShaderID() { return this->id; }
