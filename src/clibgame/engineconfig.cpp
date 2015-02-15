#include "engineconfig.hpp"

//////////
// Code //

// Creating a default EngineConfig.
clibgame::EngineConfig::EngineConfig() {
    this->title      = "clibgame Application";
    this->width      = 640;
    this->height     = 480;
    this->fullscreen = false;
    this->ups        = 120;
    this->rps        = 60;
}
