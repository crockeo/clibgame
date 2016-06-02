#include "shader.hpp"

//////////////
// Includes //
#include <iostream>
#include <fstream>
#include <sstream>

//////////
// Code //

namespace clibgame {
    namespace res {
        // Loading a single shader from the filesystem.
        Shader loadShader(std::string path, GLenum kind) throw(std::runtime_error, std::logic_error) {
            if (kind != GL_VERTEX_SHADER && kind != GL_FRAGMENT_SHADER && kind != GL_GEOMETRY_SHADER)
                throw std::logic_error("Must pass a valid GLenum -- vertex, fragment, or geometry shader.");

            std::ifstream file(path);
            file.seekg(0, file.end);
            int len = file.tellg();
            file.seekg(0, file.beg);

            char* contents = new char[len];
            file.read(contents, len);
            file.close();

            Shader shader = glCreateShader(kind);
            if (shader == 0)
                throw std::runtime_error("Could not allocate shader.");

            glShaderSource(shader, 1, &contents, nullptr);
            glCompileShader(shader);

            GLint compiled;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if (compiled == GL_FALSE) {
                GLchar log[1024];
                glGetShaderInfoLog(shader, 1024, nullptr, log);

                glDeleteShader(shader);
                delete[] contents;

                std::ostringstream str;
                str << "Failed to compile shader '" << path << "': " << std::endl
                    << "  " << log;
                throw std::runtime_error(str.str());
            }

            delete[] contents;
            return shader;
        }

        // Linking a shader program from three Shaders (vertex, fragment, and
        // geometry).
        ShaderProgram linkShaderProgram(Shader vert, Shader frag, Shader geom) throw(std::runtime_error, std::logic_error) {
            if (vert == 0 || frag == 0)
                throw std::logic_error("Cannot create a shader program without a vertex shader or fragment shader.");
            ShaderProgram program = glCreateProgram();

            if (vert != 0) glAttachShader(program, vert);
            if (frag != 0) glAttachShader(program, frag);
            if (geom != 0) glAttachShader(program, geom);

            glLinkProgram(program);

            GLint linked;
            glGetProgramiv(program, GL_LINK_STATUS, &linked);
            if (linked == GL_FALSE) {
                GLchar log[1024];
                glGetProgramInfoLog(program, 1024, nullptr, log);

                glDeleteProgram(program);

                std::ostringstream str;
                str << "Failed to link program: " << log;
                throw std::runtime_error(str.str());
            }

            return program;
        }

        // Loading an entire shader program from the file system. Effectively
        // a nice combination of loadShader(...) and linkShaderProgram(...).
        ShaderProgram loadShaderProgram(std::string basePath) throw(std::runtime_error) {
            Shader vert = loadShader(basePath + ".vert", GL_VERTEX_SHADER),
                   frag = loadShader(basePath + ".frag", GL_FRAGMENT_SHADER),
                   geom = loadShader(basePath + ".geom", GL_GEOMETRY_SHADER);

            ShaderProgram program = linkShaderProgram(vert, frag, geom);

            glDeleteShader(vert);
            glDeleteShader(frag);
            glDeleteShader(geom);

            return program;
        }
    }
}
