// Name: clibgame/timer.hpp
//
// Description:
//   This file provides a class to keep track of time for the library.

#ifndef _CLIBGAME_TIMER_HPP_
#define _CLIBGAME_TIMER_HPP_

//////////////
// Includes //
#include <thread>

//////////
// Code //

namespace clibgame {
    // A class to keep track of time.
    class Timer {
    private:
        std::thread updateThread;
        float fidelity;
        bool running;
        float time;
        float cap;
        
    public:
        // The default fidelity of the Timer.
        constexpr static float defaultFidelity = 0.01f;

        // Creating a timer with a non-standard fidelity that loops at a given
        // point (if you want it not to loop, make the first float less than 0).
        Timer(float, float);

        // Creating a timer that loops at a given point.
        Timer(float);

        // Creating a timer that doesn't loop.
        Timer();

        // Copy constructor.
        Timer(const Timer&);

        // Destroying this timer.
        ~Timer();

        // Assignment operator.
        Timer& operator=(const Timer&);

        // Some accessors.
        float getFidelity() const;
        float getTime() const;
        float getCap() const;
    };
}

#endif
