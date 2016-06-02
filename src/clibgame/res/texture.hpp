// Name     : clibgame/res/texture.hpp
// Author(s): Cerek Hillen
// Init Date: 2016-06-02
// Edit Date: 2016-06-02
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

//////////
// Code //

namespace clibgame {
    namespace res {
        // A struct that contains information about a Texture.
        struct Texture {
            int width, height;
            GLuint id;

            // Loading a texture from the filesystem.
            static Texture load(std::string path) throw(std::runtime_error);
        };
    }
}

#endif
