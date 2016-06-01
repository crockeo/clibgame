#include "pak.hpp"

//////////////
// Includes //
#include <stdlib.h>

//////////
// Code //

namespace clibgame {
    namespace res {
        ////
        // FileSystemPak

        FileSystemPak::FileSystemPak() :
                stream(),
                open(false) { }

        FileSystemPak::~FileSystemPak() {
            if (isOpen())
                closeFile();
        }
        
        // Opening a file and returning a std::ifstream& to its location.
        std::istream& FileSystemPak::openFile(std::string path) throw(std::runtime_error, std::logic_error) {
            if (isOpen())
                throw std::logic_error("Cannot open a file when another is already open.");
            stream = std::ifstream(path);
            open = true;
            return stream;
        }

        // Closing a file -- should close the opened std::ifstream& if need
        // be.
        void FileSystemPak::closeFile() throw(std::logic_error) {
            if (!isOpen())
                throw std::logic_error("Cannot close a non-open file.");
            stream.close();
            open = false;
        }

        // Checking if a file is open.
        bool FileSystemPak::isOpen() const { return open; }

        ////
        // PakReader

        ////
        // RealPak

        // Reading in from the std::ifstream to populate the files object.
        bool RealPak::initFiles() {
            // TODO: Populate files after I decide on an asset spec.
        }

        RealPak::RealPak(std::string path) :
                files(),
                reader(path),
                open(false) {
            if (!initFiles())
                throw std::runtime_error("Failed to initialize .pak file.");
        }

        // Opening a file and returning a std::ifstream& to its location.
        std::istream& RealPak::openFile(std::string path) throw(std::logic_error) {
            if (isOpen())
                throw std::logic_error("Cannot open a file when another is already open.");
            // TODO: Open file.
        }

        // Closing a file -- should close the opened std::ifstream& if need
        // be.
        void RealPak::closeFile() throw(std::logic_error) {
            if (!open)
                throw std::logic_error("Cannot close a non-open file.");
            open = false;
        }

        // Checking if a file is open.
        bool RealPak::isOpen() const { return open; }
    }
}
