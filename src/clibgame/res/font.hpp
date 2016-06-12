#ifndef _CLIBGAME_RES_FONT_HPP_
#define _CLIBGAME_RES_FONT_HPP_

//////////////
// Includes //
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>

#include "resource.hpp"

//////////
// Code //

namespace clibgame {
    namespace res {
        // A TTF font (using libttf).
        class Font : public Resource {
        private:
            FT_Face _face;
            bool _loaded;
            int _pnt;

        public:
            Font(int pnt);
            Font();

            // Loading a Resource from a variety of places.
            virtual void load(clibgame::core::Pak& pak, std::string path)
                    throw(std::runtime_error);

            // Disposing of an already-loaded resource.
            virtual void dispose()
                    throw(std::runtime_error);

            // Checking if this resource has been loaded.
            virtual bool loaded() const;

            // Getting the size of a render for a given string.
            float displayWidth(std::string str) const;
            float displayHeight(std::string str) const;
            std::tuple<float, float> displaySize(std::string str) const;

            // Accessors.
            const FT_Face face() const;
            int pnt() const;

            // Setting the point of this font.
            void setPnt(int pnt);
        };
    }
}

#endif
