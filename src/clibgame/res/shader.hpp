// Name     : clibgame/res/shader.hpp
// Author(s): Cerek Hillen
// Init Date: 2016-06-02
// Edit Date: 2016-06-06
//
// Description:
//   Utilities to load shaders and shader programs from the filesystem.

#ifndef _CLIBGAME_RES_SHADER_HPP_
#define _CLIBGAME_RES_SHADER_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <string>

#include "resource.hpp"

//////////
// Code //

namespace clibgame {
    namespace res {
        // A class to represent OpenGL shader programs. Automatically attempts
        // to load the .vert, .frag, and .geom shaders when loading.
        class ShaderProgram : public Resource {
        private:
            GLuint _id;
            bool _loaded;

            // Loading a shader from an istream.
            GLuint loadShader(std::istream& input, GLenum kind) const
                    throw(std::runtime_error);

        public:
            ShaderProgram();

            // Getting the ID of this ShaderProgram.
            GLuint id() const;

            // Loading a Resource from a variety of places.
            virtual void load(clibgame::core::Pak& pak, std::string path)
                    throw(std::runtime_error);

            // Disposing of an already-loaded resource.
            virtual void dispose()
                    throw(std::runtime_error);

            // Checking if this resource has been loaded.
            virtual bool loaded() const;
        };
    }
}

#endif
