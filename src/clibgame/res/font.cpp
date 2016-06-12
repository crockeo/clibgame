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

        Font::Font(int pnt) :
                _loaded(false),
                _pnt(pnt) { }

        Font::Font() :
                Font(16) { }

        // Loading a Resource from a variety of places.
        void Font::load(clibgame::core::Pak& pak, std::string path)
                throw(std::runtime_error) {
            // TODO: Find out how to move this over to a FILE* directly.
            if (FT_New_Face(FontLib::instance(), path.c_str(), 0, &_face))
                throw std::runtime_error("Failed to load font from '" + path + "'!");
            FT_Set_Pixel_Sizes(_face, 0, _pnt);
        }

        // Disposing of an already-loaded resource.
        void Font::dispose()
                throw(std::runtime_error) {
            // TODO: Dispose of this.
        }

        // Checking if this resource has been loaded.
        bool Font::loaded() const { return _loaded; }

        // Getting the size of a render for a given string.
        float Font::displayWidth(std::string str) const {
            // TODO
        }

        float Font::displayHeight(std::string str) const { return _pnt; }

        std::tuple<float, float> Font::displaySize(std::string str) const {
            return std::make_tuple(displayWidth(str), displayHeight(str));
        }

        // Setting the point of this font.
        void Font::setPnt(int pnt) {
            _pnt = pnt;
            FT_Set_Pixel_Sizes(_face, 0, _pnt);
        }
    }
}
