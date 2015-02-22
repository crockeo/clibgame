//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <clibgame.hpp>
#include <iostream>

#include "game.hpp"

//////////
// Code //

// The entry point.
int main(int argc, char** argv) {
    clibgame::EngineConfig cfg;

    cfg.ups = 240;
    cfg.rps = 120;

    Game game;

    try {
        clibgame::startEngine(cfg, game, "res/assetspec.txt");
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
