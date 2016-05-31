// Name     : clibgame/core/uuid.hpp
// Author(s): Cerek Hillen
// Init Date: 2016-05-29
// Edit Date: 2016-05-31
//
// Description:
//   A cross-platform implementation of UUIDs and a UUID generator. Effectively
//   an array of random bytes.

#ifndef _CLIBGAME_CORE_UUID_HPP_
#define _CLIBGAME_CORE_UUID_HPP_

//////////////
// Includes //
#include <vector>

//////////
// Code //

namespace clibgame {
    namespace core {
        const static int DEFAULT_UUID_SIZE = 16;

        // A cross-platform unique identifier.
        class UUID {
        private:
            std::vector<unsigned char> bytes;

            // Creating a UUID with a set of bytes and byte length.
            UUID(std::vector<unsigned char>);

        public:
            // Generating a new UUID with a described UUID size.
            static UUID generateUUIDLen(int);

            // Generating a new UUID with the default UUID size.
            static UUID generateUUID();

            // Checking equality and inequality of UUIDS.
            bool operator==(const UUID&) const;
            bool operator!=(const UUID&) const;

            // Ordering UUIDs -- used in ordered collections.
            bool operator<(const UUID&) const;

            // Getting the bytes from the UUID.
            const std::vector<unsigned char>& getBytes() const;

            // Getting a byte at a given location.
            unsigned char getByte(int i) const;

            // Getting the size of the byte string.
            int getSize() const;
        };
    }
}

namespace std {
    // Providing ordering and hashing for UUIDs so they can be used in organized
    // data structures.

    // Hashing.
    template <>
    struct hash<clibgame::core::UUID> {
        std::size_t operator()(const clibgame::core::UUID&) const;
    };
}

#endif
