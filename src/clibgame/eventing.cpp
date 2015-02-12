#include "eventing.hpp"

//////////
// Code //

std::unique_ptr<clibgame::ListenerManager> clibgame::ListenerManager::lm = nullptr;

// Creating the ListenerManager.
clibgame::ListenerManager::ListenerManager() { }

// Getting the global instance of the ListenrManager.
clibgame::ListenerManager& clibgame::ListenerManager::instance() {
    if (lm == nullptr)
        lm = std::unique_ptr<ListenerManager>(new clibgame::ListenerManager());
    return *lm;
}

// Registering a Listener.
void clibgame::ListenerManager::registerListener(Listener* l, std::string type) {
    this->listeners[type].insert(l);
}

// Removing a Listener.
void clibgame::ListenerManager::removeListener(Listener* l, std::string type) {
    this->listeners[type].erase(this->listeners[type].find(l));
}

// Alerting the ListenerManager of a given event.
void clibgame::ListenerManager::alert(const Event&& e) {
    for (auto l: this->listeners[e.getEventType()])
        l->alert(std::move(e));
}
