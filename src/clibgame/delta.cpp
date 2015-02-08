#include "delta.hpp"

//////////////
// Includes //
#include <thread>
#include <chrono>

//////////
// Code //

// Getting the current time in seconds from the last epoch.
float clibgame::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

// Delaying the current thread for a given period of seconds.
void clibgame::delayThread(float seconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(seconds * 1000)));
}

// Creating a new delta.
clibgame::Delta::Delta() {
    this->last = 0.f;
    this->curr = 0.f;
}

// Getting the time since the last update.
float clibgame::Delta::since() {
    this->last = this->curr;
    this->curr = clibgame::getCurrentTime();

    if (this->last == 0.f)
        return 0.f;

    return this->curr - this->last;
}
