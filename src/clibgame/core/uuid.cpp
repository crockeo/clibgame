#include "uuid.hpp"

//////////////
// Includes //
#include <stddef.h>
#include <fstream>

//////////
// Code //

namespace clibgame {
    namespace core {
        // Creating a UUID with a set of bytes and byte length.
        UUID::UUID(std::vector<unsigned char> bytes) :
                bytes(bytes) { }

        // Generating a new UUID with a described UUID size.
        UUID UUID::generateUUIDLen(int len) {
#if defined(__linux__) || defined(__APPLE__)
            // Linux / Mac implementation.
            std::vector<unsigned char> data(len);
            std::ifstream rand("/dev/random");
            rand.read((char*)&data[0], len);
            rand.close();

            return UUID(data);
#endif

#if defined(WIN32) || defined(__MINGW32__)
            // TODO: Windows implementation.
#endif
        }

        // Generating a new UUID with the default UUID size.
        UUID UUID::generateUUID() {
            return generateUUIDLen(DEFAULT_UUID_SIZE);
        }

        // Checking equality and inequality of UUIDS.
        bool UUID::operator==(const UUID& other) const {
            return this->getBytes() == other.getBytes();
        }

        bool UUID::operator!=(const UUID& other) const {
            return !(*this == other);
        }

        // Ordering UUIDs -- used in ordered collections.
        bool UUID::operator<(const UUID& other) const {
            for (int i = 0; i < getSize() && i < other.getSize(); i++) {
                if (getByte(i) < other.getByte(i))
                    return true;
                if (getByte(i) > other.getByte(i))
                    return false;
            }

            return getSize() < other.getSize();
        }

        // Getting the bytes from the UUID.
        const std::vector<unsigned char>& UUID::getBytes() const {
            return this->bytes;
        }

        // Getting a byte at a given location.
        unsigned char UUID::getByte(int i) const {
            return getBytes().at(i);
        }

        // Getting the size of the byte string.
        int UUID::getSize() const {
            return this->bytes.size();
        }
    }
}

namespace std {
    // Providing ordering and hashing for UUIDs so they can be used in organized
    // data structures.

    // Hashing.
    std::size_t hash<clibgame::core::UUID>::operator()(const clibgame::core::UUID& uuid) const {
        return std::hash<const unsigned char*>()(&uuid.getBytes()[0]);
    }
}
