#include "font.hpp"

//////////////
// Includes //
#include <iostream>

//////////
// Code //

namespace clibgame {
    namespace res {
        ////
        // FontLib

        // The global instance of the FreeType font library.
        class FontLib {
        private:
            static std::unique_ptr<FT_Library> ft;

        public:
            // Getting the global FT_Library instance.
            static FT_Library instance();
        };

        std::unique_ptr<FT_Library> FontLib::ft = nullptr;

        // Getting the global FT_Library instance.
        FT_Library FontLib::instance() {
            if (FontLib::ft == nullptr) {
                FT_Library* ft = new FT_Library;
                FT_Init_FreeType(ft);

                FontLib::ft = std::unique_ptr<FT_Library>(ft);
            }

            return *FontLib::ft;
        }

        ////
        // Font

        // Loading a Font from a given location on disk.
        Font Font::load(std::string path, int pnt) throw(std::runtime_error) {
            Font font;

            font.face = nullptr;
            if (FT_New_Face(FontLib::instance(), path.c_str(), 0, &font.face))
                throw std::runtime_error("Failed to load font from '" + path + "'!");

            FT_Set_Pixel_Sizes(font.face, 0, pnt);
            font.pnt = pnt;

            return font;
        }

        // Getting the size of a render for a given string.
        float Font::displayWidth(std::string str) const {
            // TODO: Return display width for a string.
            return 0.f;
        }

        float Font::displayHeight(std::string str) const {
            return pnt;
        }

        std::tuple<float, float> Font::displaySize(std::string str) const {
            return std::make_tuple(displayWidth(str), displayHeight(str));
        }
    }
}
