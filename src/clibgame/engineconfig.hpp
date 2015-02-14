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

        // Initializing a configuration.
        EngineConfig(std::string, int, int, bool);
    };
};

#endif
