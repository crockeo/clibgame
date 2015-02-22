#include "font.hpp"

//////////////
// Includes //
#include <iostream>

//////////
// Code //

std::unique_ptr<FT_Library> clibgame::FontLib::ft = nullptr;

// Getting the global FT_Library instance.
FT_Library clibgame::FontLib::instance() {
    if (clibgame::FontLib::ft == nullptr) {
        FT_Library* ft = new FT_Library;
        FT_Init_FreeType(ft);

        clibgame::FontLib::ft = std::unique_ptr<FT_Library>(ft);
    }

    return *clibgame::FontLib::ft;
}

clibgame::Font::Font(std::string path, int pnt) throw(std::runtime_error) {
    this->fontFace = nullptr;

    if (FT_New_Face(FontLib::instance(), path.c_str(), 0, &this->fontFace))
        throw std::runtime_error("Failed to load font from '" + path + "'!");

    FT_Set_Pixel_Sizes(this->fontFace, 0, pnt);
    this->original = true;
    this->pnt      = pnt;
}

// Copy constructor.
clibgame::Font::Font(const Font& font) {
    this->original = false;

    this->fontFace = font.fontFace;
    this->pnt      = font.pnt;
}

// Destroying this font.
clibgame::Font::~Font() {
    if (this->original)
        if (this->fontFace != nullptr)
            FT_Done_Face(this->fontFace);
}

// Determining the display width of a string.
float clibgame::Font::displayWidth(std::string str) const {
    float x = 0;

    for (const char* ptr = str.c_str(); *ptr; ptr++) {
        if (FT_Load_Char(this->fontFace, *ptr, FT_LOAD_RENDER))
            continue;
        x += this->fontFace->glyph->advance.x >> 6;
    }

    return x;
}

// Determining the display height of a string.
float clibgame::Font::displayHeight(std::string str) const {
    return this->pnt;
}

// Getting the FT_Face of this font.
FT_Face clibgame::Font::getFontFace() const {
    return this->fontFace;
}

// Getting the height of this font - it will always be the same as
// displayWidth; only an 'int' instead of a 'float'.
int clibgame::Font::getPnt() const {
    return this->pnt;
}
