// Name     : clibgame/core/debug.hpp
// Author(s): Cerek Hillen
// Init Date: 2016-05-30
// Edit Date: 2016-05-30
//
// Description:
//   Manages the global "debug level" within the project -- when lower the
//   project prints less debug information.

#ifndef _CLIBGAME_CORE_DEBUG_HPP_
#define _CLIBGAME_CORE_DEBUG_HPP_

//////////
// Code //

namespace clibgame {
    namespace core {
        // A container for Debug information.
        class Debug {
        private:
            static int _level;

        public:
            // Changing the current Debug level (if n < -1, it only accesses the
            // debug level and doesn't change it).
            static int level(int n);

            // Accessing the current Debug level.
            static int level();
        };
    }
}

#endif
