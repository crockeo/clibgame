#include "sound.hpp"

namespace clibgame {
    namespace res {
        ////
        // Sound

        // TODO: lots of cool sound things.

        Sound::Sound() {

        }

        // Loading a Resource from a variety of places.
        void Sound::load(clibgame::core::Pak& pak, std::string path)
                throw(std::runtime_error) {

        }

        // Disposing of an already-loaded resource.
        void Sound::dispose()
                throw(std::runtime_error) {
        }

        // Checking if this resource has been loaded.
        bool Sound::loaded() const { return false; }
    }
}
