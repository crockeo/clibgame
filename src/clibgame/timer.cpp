#include "timer.hpp"

//////////////
// Includes //
#include <chrono>

//////////
// Code //

namespace clibgame {
    // The update loop function for the timer.
    void updateTimerFn(const float& fidelity, const bool& running, const float& cap, float& time) {
        float last = 0.f,
              now  = 0.f;

        while (running) {
            // TODO: Update the time.
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(fidelity * 1000)));
        }
    }
}

// Creating a timer with a non-standard fidelity that loops at a given
// point (if you want it not to loop, make the first float less than 0).
clibgame::Timer::Timer(float cap, float fidelity) {
    this->fidelity = fidelity;
    this->running  = true;
    this->time     = 0.f;
    this->cap      = cap;

    this->updateThread = std::thread(
        clibgame::updateTimerFn,
        std::cref(this->fidelity),
        std::cref(this->running),
        std::cref(this->cap),
        std::ref(this->time)
    );
}

// Creating a timer that loops at a given point.
clibgame::Timer::Timer(float cap) :
        clibgame::Timer(cap, clibgame::Timer::defaultFidelity) { }

// Creating a timer that doesn't loop.
clibgame::Timer::Timer() :
        clibgame::Timer(-1) { }

// Copy constructor.
clibgame::Timer::Timer(const Timer& timer) :
        clibgame::Timer(timer.cap, timer.fidelity) {
    this->time = timer.time;
}

// Destroying this timer.
clibgame::Timer::~Timer() {
    this->running = false;
    this->updateThread.join();
}

// Assignment operator.
clibgame::Timer& clibgame::Timer::operator=(const Timer& timer) {
    // Cleaning up this thingy.
    this->running = false;
    this->updateThread.join();

    // Setting this thingy to another thingy.
    this->fidelity = timer.fidelity;
    this->running = timer.running;
    this->time = timer.time;
    this->cap = timer.cap;

    if (this->running) {
        this->updateThread = std::thread(
            clibgame::updateTimerFn,
            std::cref(this->fidelity),
            std::cref(this->running),
            std::cref(this->cap),
            std::ref(this->time)
        );
    }

    return *this;
}

// Some accessors.
float clibgame::Timer::getFidelity() const { return this->fidelity; }
float clibgame::Timer::getTime() const { return this->time; }
float clibgame::Timer::getCap() const { return this->cap; }
