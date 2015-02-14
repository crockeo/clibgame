#include "engine.hpp"

//////////
// Code //

// Starting the engine from an ECP derivative and a Res derivative.
void clibgame::startEngine(ECP& ecp, const Res& resources) throw(std::runtime_error) {
    throw std::runtime_error("Starting engine not here yet. kek");
}

// Starting the engine from an ECP derivative and the location of a set of
// resources.
void clibgame::startEngine(ECP& ecp, std::string path) throw(std::runtime_error) {
    Res resources;

    try {
        clibgame::loadRes(resources, path);
    } catch (std::runtime_error& e) {
        throw e;
    }

    clibgame::startEngine(ecp, resources);
}
