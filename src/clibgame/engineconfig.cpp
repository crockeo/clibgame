#include "engineconfig.hpp"

// Initializing a configuration.
clibgame::EngineConfig::EngineConfig(std::string title, int width, int height, bool fullscreen) {
    this->title = title;
    this->width = width;
    this->height = height;
    this->fullscreen = fullscreen;
}
