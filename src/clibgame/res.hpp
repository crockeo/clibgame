#ifndef _CLIBGAME_RES_HPP_
#define _CLIBGAME_RES_HPP_

//////////////
// Includes //
#include <unordered_map>
#include <memory>

#include "res/animation.hpp"
#include "res/texsheet.hpp"
#include "res/texture.hpp"
#include "res/shader.hpp"

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

    public:
        // Creating an empty Res.
        Res();

        // Adding a set of resources.
        void addAnimation(std::string, int, int, float, bool);
        void addAnimation(std::string, int, int, float);
        void addTexSheet(std::string, int, int);
        void addTexture(std::string);
        void addShader(std::string);

        // Getting a set of resources.
        Animation getAnimation(std::string) const;
        TexSheet getTexSheet(std::string) const;
        Texture getTexture(std::string) const;
        Shader getShader(std::string) const;
    };
}

#endif
