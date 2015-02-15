#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

//////////////
// Includes //
#include <string>

//////////
// Code //

namespace clibgame {
    struct EngineConfig {
        std::string title;
        int width, height;
        bool fullscreen;
        int ups, rps;

        // Creating a default EngineConfig.
        EngineConfig();
    };
};

#endif
