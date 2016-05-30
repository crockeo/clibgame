#include "debug.hpp"

//////////
// Code //

namespace clibgame {
    namespace core {
        ////
        // Debug

        int Debug::_level = 0;

        // Changing the current Debug level (if n < -1, it only accesses the
        // debug level and doesn't change it).
        int Debug::level(int n) {
            if (n >= 0)
                _level = n;
            return _level;
        }

        // Accessing the current Debug level.
        int Debug::level() {
            return _level;
        }
    }
}
