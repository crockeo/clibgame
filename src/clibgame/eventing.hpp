#ifndef _CLIBGAME_EVENTING_HPP_
#define _CLIBGAME_EVENTING_HPP_

//////////////
// Includes //
#include <unordered_map>
#include <memory>
#include <string>
#include <set>

//////////
// Code //

namespace clibgame {
    // A type to represent an event.
    struct Event {
        // Getting the type of the event.
        virtual std::string getEventType() const = 0;
    };

    // The abstract Listener class.
    struct Listener {
        // Alerting the Listener of a given event.
        virtual void alert(const Event&&) = 0;
    };

    // The global Listener manager.
    class ListenerManager : public Listener {
    private:
        static std::unique_ptr<ListenerManager> lm;

        std::unordered_map<std::string, std::set<Listener*>> listeners;

        // Creating the ListenerManager.
        ListenerManager();

    public:
        // Getting the global instance of the ListenrManager.
        static ListenerManager& instance();

        // Registering a Listener.
        void registerListener(Listener*, std::string);

        // Removing a Listener.
        void removeListener(Listener*, std::string);

        // Alerting the ListenerManager of a given event.
        void alert(const Event&&);
    };
}

#endif
