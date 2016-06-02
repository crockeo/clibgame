#ifndef _CLIBGAME_RES_FONT_HPP_
#define _CLIBGAME_RES_FONT_HPP_

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <memory>
#include <string>

//////////
// Code //

namespace clibgame {
    namespace res {
        // A font from the filesystem.
        struct Font {
            FT_Face face;
            int pnt;

            // Loading a Font from a given location on disk.
            static Font load(std::string path, int pnt) throw(std::runtime_error);

            // Getting the size of a render for a given string.
            float displayWidth(std::string str) const;
            float displayHeight(std::string str) const;
            std::tuple<float, float> displaySize(std::string str) const;
        };
    }
}

#endif
