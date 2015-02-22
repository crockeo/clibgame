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
        int pnt;

    public:
        // Loading a font from a location on disk.
        Font(std::string, int);

        // Copy constructor.
        Font(const Font&);

        // Destroying this font.
        ~Font();

        // Deleting the assignment operator.
        Font& operator=(const Font&) = delete;

        // Determining the display width of a string.
        float displayWidth(std::string) const;

        // Determining the display height of a string.
        float displayHeight(std::string) const;

        // Getting the FT_Face of this font.
        FT_Face getFontFace() const;

        // Getting the height of this font - it will always be the same as
        // displayWidth; only an 'int' instead of a 'float'.
        int getPnt() const;
    };
}

#endif
