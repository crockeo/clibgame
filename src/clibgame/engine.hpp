// Name: clibgame/engine.hpp
//
// Description:
//   This module provides the API to start the engine surrounding clibgame.

#ifndef _CLIBGAME_ENGINE_HPP_
#define _CLIBGAME_ENGINE_HPP_

//////////////
// Includes //
#include <string>

#include "engineconfig.hpp"
#include "ecp.hpp"
#include "res.hpp"

//////////
// Code //

namespace clibgame {
    // Starting the engine from an ECP derivative and the location of a set of
    // resources.
    void startEngine(EngineConfig, ECP&, std::string) throw(std::runtime_error);
}

#endif
