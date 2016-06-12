// Name     : clibgame/res/sound.hpp
// Author(s): Cerek Hillen
// Init Date: 2016-06-03
// Edit Date: 2016-06-03
//
// Description:
//   Loading sounds (.ogg) files from the filesystem.

#ifndef _CLIBGAME_RES_SOUND_HPP_
#define _CLIBGAME_RES_SOUND_HPP_

//////////////
// Includes //
#include "resource.hpp"

//////////
// Code //

namespace clibgame {
    namespace res {
        class Sound : public Resource {
        public:
            Sound();

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
