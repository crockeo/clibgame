// Name: clibgame/res/animation.hpp
//
// Description:
//   This file provides the API to deal with animations.

#ifndef _CLIBGAME_RES_ANIMATION_HPP_
#define _CLIBGAME_RES_ANIMATION_HPP_

//////////////
// Includes //
#include <tuple>

#include "../timer.hpp"
#include "texsheet.hpp"
#include "texable.hpp"

//////////
// Code //

namespace clibgame {
    // The animation class itself.
    class Animation : public Texable {
    private:
        clibgame::TexSheet texSheet;
        int beginFrame, endFrame;
        float frameLength;
        Timer timer;
        bool loop;

        // Getting the row and column of the current frame.
        std::tuple<int, int> getCurrentFrame() const;

    public:
        // Loading an Anumation from the file system with an option of whether
        // or not it should loop and a specific start frame and end frame.
        Animation(std::string, int, int, float, bool, int, int) throw(std::runtime_error);

        // Loading an animation from the file system that will always loop and a
        // specific start frame and end frame.
        Animation(std::string, int, int, float, int, int) throw(std::runtime_error);

        // Loading an Animation from the file system with an option of whether
        // or not it should loop.
        Animation(std::string, int, int, float, bool) throw(std::runtime_error);

        // Loading an animation from the file system that will always loop.
        Animation(std::string, int, int, float) throw(std::runtime_error);

        // Getting the ID of the animation.
        GLuint getTextureID() const;

        // Getting the texture coordinates of this thingy.
        std::vector<GLfloat> getTextureCoords() const;
    };
}

#endif
