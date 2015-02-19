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
    // The global instance of the FreeType font library.
    class FontLib {
    private:
        static std::unique_ptr<FT_Library> ft;

    public:
        // Getting the global FT_Library instance.
        static FT_Library instance();
    };

    // A class to represent a type of font.
    class Font {
    private:
        FT_Face fontFace;
        bool original;
        GLuint ebo;
        int pnt;
        int len;

    public:
        // TODO: Actually do some font loading.
    };
}

#endif
