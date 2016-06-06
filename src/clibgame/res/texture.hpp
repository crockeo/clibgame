// Name     : clibgame/res/texture.hpp
// Author(s): Cerek Hillen
// Init Date: 2016-06-02
// Edit Date: 2016-06-06
//
// Description:
//

// Name: clibgame/res/texture.hpp
//
// Description:
//   This is meant to contain information surrounding the creation and use of
//   textures.

#ifndef _CLIBGAME_RES_TEXTURE_
#define _CLIBGAME_RES_TEXTURE_

//////////////
// Includes //
#include <GL/glew.h>
#include <string>
#include <vector>

#include "resource.hpp"

//////////
// Code //

namespace clibgame {
    namespace res {
        // A struct that contains information about a Texture.
        class Texture : public Resource {
        private:
            int _width, _height;
            bool _loaded;
            GLuint _id;

        public:
            Texture();

            // Getting the size of the texture.
            int getWidth() const;
            int getHeight() const;

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
