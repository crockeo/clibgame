// Name     : clibgame/res/resource.hpp
// Author(s): Cerek Hillen
// Init Date: 2016-06-06
// Edit Date: 2016-06-06
//
// Description:
//   A unified API for one to work with resources.

#ifndef _CLIBGAME_RES_RESOURCE_HPP_
#define _CLIBGAME_RES_RESOURCE_HPP_

//////////////
// Includes //
#include "../core/pak.hpp"

//////////
// Code //

namespace clibgame {
    namespace res {
        // The (entirely virtual) class that defines the Resource API.
        struct Resource {
            virtual ~Resource() { }

            // Loading a Resource from a variety of places.
            virtual void load(clibgame::core::Pak& pak, std::string path)
                    throw(std::runtime_error) = 0;

            // Disposing of an already-loaded resource.
            virtual void dispose()
                    throw(std::runtime_error) = 0;

            // Checking if this resource has been loaded.
            virtual bool loaded() const = 0;
        };
    }
}

#endif
