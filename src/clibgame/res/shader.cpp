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
        ////
        // ShaderProgram

        // Loading a shader from an istream.
        GLuint ShaderProgram::loadShader(FILE* file, GLenum kind) const
                throw(std::runtime_error) {
            fseek(file, 0, SEEK_END);
            int len = ftell(file);
            fseek(file, 0, SEEK_SET);

            char* contents = new char[len];
            fread(contents, 1, len, file);

            GLuint shader = glCreateShader(kind);
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
                str << "Failed to compile shader: " << std::endl
                    << "  " << log;
                throw std::runtime_error(str.str());
            }

            return shader;
        }

        // Getting the ID of this ShaderProgram.
        GLuint ShaderProgram::id() const { return _id; }

        // Loading a Resource from a variety of places.
        void ShaderProgram::load(clibgame::core::Pak& pak, std::string path)
                throw(std::runtime_error) {
            GLuint vert = 0,
                   frag = 0,
                   geom = 0;

            if (pak.hasFile(path + ".vert")) {
                vert = loadShader(pak.openFile(path + ".vert"), GL_VERTEX_SHADER);
                pak.closeFile();
            }

            if (pak.hasFile(path + ".frag")) {
                frag = loadShader(pak.openFile(path + ".frag"), GL_VERTEX_SHADER);
                pak.closeFile();
            }

            if (pak.hasFile(path + ".geom")) {
                geom = loadShader(pak.openFile(path + ".geom"), GL_VERTEX_SHADER);
                pak.closeFile();
            }

            if (vert == 0 || frag == 0) {
                std::ostringstream str;
                str << "Shader program '" << path << "' does not have either a vertex shader or a fragment shader.";
                throw std::runtime_error(str.str());
            }

            _id = glCreateProgram();
            glAttachShader(_id, vert);
            glAttachShader(_id, frag);
            glAttachShader(_id, geom);

            glLinkProgram(_id);

            glDeleteShader(vert);
            glDeleteShader(frag);
            glDeleteShader(geom);

            GLint linked;
            glGetProgramiv(_id, GL_LINK_STATUS, &linked);
            if (linked == GL_FALSE) {
                GLchar log[1024];
                glGetProgramInfoLog(_id, 1024, nullptr, log);

                glDeleteProgram(_id);

                std::ostringstream str;
                str << "Failed to link _id: " << log;
                throw std::runtime_error(str.str());
            }
        }

        // Disposing of an already-loaded resource.
        void ShaderProgram::dispose()
                throw(std::runtime_error) {
            glDeleteProgram(_id);
        }

        // Checking if this resource has been loaded.
        bool ShaderProgram::loaded() const { return _loaded; }
    }
}
