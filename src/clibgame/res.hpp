// Name: clibgame/res.hpp
//
// Description:
//   This module provides asset management for the asset types contained in
//   clibgame/res/

#ifndef _CLIBGAME_RES_HPP_
#define _CLIBGAME_RES_HPP_

//////////////
// Includes //
#include <unordered_map>
#include <istream>
#include <memory>

#include "res/animation.hpp"
#include "res/texsheet.hpp"
#include "res/texture.hpp"
#include "res/shader.hpp"
#include "res/font.hpp"

//////////
// Code //

namespace clibgame {
    // A class to represent a set of resources.
    class Res {
    private:
        std::unordered_map<std::string, clibgame::Animation> animations;
        std::unordered_map<std::string, clibgame::TexSheet> texSheets;
        std::unordered_map<std::string, clibgame::Texture> textures;
        std::unordered_map<std::string, clibgame::Shader> shaders;
        std::unordered_map<std::string, clibgame::Font> fonts;

    public:
        // Creating an empty Res.
        Res();

        // Deleting the copy constructor.
        Res(const Res&) = delete;

        // Deleting the assignment operator.
        Res& operator=(const Res&) = delete;

        // Adding a set of resources.
        void addAnimation(std::string, int, int, float, bool, int, int) throw(std::runtime_error);
        void addAnimation(std::string, int, int, float, bool) throw(std::runtime_error);
        void addAnimation(std::string, int, int, float) throw(std::runtime_error);
        void addTexSheet(std::string, int, int) throw(std::runtime_error);
        void addTexture(std::string) throw(std::runtime_error);
        void addShader(std::string) throw(std::runtime_error);
        void addFont(std::string, int) throw(std::runtime_error);

        // Getting a set of resources.
        Animation getAnimation(std::string) const;
        TexSheet getTexSheet(std::string) const;
        Texture getTexture(std::string) const;
        Shader getShader(std::string) const;
        Font getFont(std::string) const;
    };

    // Loading a set of resources from an std::istream.
    void loadRes(Res&, std::istream&) throw (std::runtime_error);

    // Loading a set of resources from a file.
    void loadRes(Res&, std::string) throw(std::runtime_error);
}

#endif
