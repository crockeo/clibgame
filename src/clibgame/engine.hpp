// Name: clibgame/engine.hpp
//
// Description:
//   This module provides the API to start the engine surrounding clibgame.

#ifndef _CLIBGAME_ENGINE_HPP_
#define _CLIBGAME_ENGINE_HPP_

//////////////
// Includes //
#include <string>

#include "ecp.hpp"
#include "res.hpp"

//////////
// Code //

namespace clibgame {
    // Starting the engine from an ECP derivative and a Res derivative.
    void startEngine(ECP&, const Res&) throw(std::runtime_error);

    // Starting the engine from an ECP derivative and the location of a set of
    // resources.
    void startEngine(ECP&, std::string) throw(std::runtime_error);
}

#endif
