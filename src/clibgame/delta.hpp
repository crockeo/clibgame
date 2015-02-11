// Name: clibgame/delta.hpp
//
// Description:
//   This class provides a utility to keep track of the amount of time between
//   requests.

#ifndef _CLIBGAME_DELTA_HPP_
#define _CLIBGAME_DELTA_HPP_

//////////
// Code //

namespace clibgame {
    // Getting the current time in seconds from the last epoch.
    long getCurrentTime();

    // Delaying the current thread for a given period of seconds.
    void delayThread(float);

    // The delta-time class.
    class Delta {
    private:
        long last, curr;

    public:
        // Creating a new delta.
        Delta();

        // Getting the time since the last update.
        float since();
    };
}

#endif
