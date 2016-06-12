#include "pak.hpp"

//////////////
// Includes //
#include <stdlib.h>

//////////
// Code //

namespace clibgame {
    namespace core {
        ////
        // FileSystemPak

        FileSystemPak::FileSystemPak() {
            fp = nullptr;
            open = false;
        }

        FileSystemPak::~FileSystemPak() {
            if (isOpen())
                closeFile();
        }
        
        // Checking if a given file exists within the Pak.
        bool FileSystemPak::hasFile(std::string path) const {
            FILE* f = fopen(path.c_str(), "r");
            bool o = f != nullptr;
            fclose(f);
            return o;
        }

        // 'Opening' a file and providing a FILE pointer to is location.
        FILE* FileSystemPak::openFile(std::string path, std::string options)
                throw(std::runtime_error, std::logic_error) {
            if (isOpen())
                throw std::logic_error("Pak already has an open file.");
            if (!hasFile(path))
                throw std::logic_error("Pak does not have file requested.");

            fp = fopen(path.c_str(), options.c_str());
            if (fp == nullptr)
                throw std::runtime_error("Failed to open file.");

            return fp;
        }

        // Closing the currently-open file.
        void FileSystemPak::closeFile()
                throw(std::logic_error) {
            if (!isOpen())
                throw std::logic_error("Pak does not have an open file.");
            fclose(fp);
            fp = nullptr;
        }

        // Checking if a file is currently open.
        bool FileSystemPak::isOpen() const {
            return fp != nullptr;
        }

        ////
        // RealPak

        // Reading in from the std::ifstream to populate the files object.
        bool RealPak::initFiles() {

        }

        RealPak::RealPak(const char* path) {
            fp = fopen(path, "r");
        }

        RealPak::RealPak(std::string path) :
                RealPak(path.c_str()) { }

        // Constructing a new RealPak file to the 'outPath' from every file
        // listed in 'paths'.
        void RealPak::construct(std::string outPath, std::vector<std::string> paths)
                throw(std::runtime_error) {

        }

        // Validating that a .pak file at least *seems* to be structured
        // properly.
        bool RealPak::validate(std::string pakPath) {

        }

        // Checking if a given file exists within the Pak.
        bool RealPak::hasFile(std::string path) const {

        }

        // 'Opening' a file and providing a FILE pointer to is location.
        FILE* RealPak::openFile(std::string path, std::string options)
                throw(std::runtime_error, std::logic_error) {
            // TODO
            return nullptr;
        }

        // Closing the currently-open file.
        void RealPak::closeFile()
                throw(std::logic_error) {

        }

        // Checking if a file is currently open.
        bool RealPak::isOpen() const {

        }

        //////
        //// PakReader

        //////
        //// RealPak

        //// Reading in from the std::ifstream to populate the files object.
        //bool RealPak::initFiles() {
            //// TODO: Populate files after I decide on an asset spec.
        //}

        //RealPak::RealPak(std::string path) :
                //files(),
                //reader(path),
                //open(false) {
            //if (!initFiles())
                //throw std::runtime_error("Failed to initialize .pak file.");
        //}

        //// Opening a file and returning a std::ifstream& to its location.
        //std::istream& RealPak::openFile(std::string path) throw(std::logic_error) {
            //if (isOpen())
                //throw std::logic_error("Cannot open a file when another is already open.");
            //// TODO: Open file.
        //}

        //// Closing a file -- should close the opened std::ifstream& if need
        //// be.
        //void RealPak::closeFile() throw(std::logic_error) {
            //if (!open)
                //throw std::logic_error("Cannot close a non-open file.");
            //open = false;
        //}

        //// Checking if a file is open.
        //bool RealPak::isOpen() const { return open; }

        //////
        //// Global Functions

        //// Constructing a PAK file from a vector of files on the filesystem.
        //void constructPakFile(std::string outPath, std::vector<std::string> paths) throw(std::runtime_error) {
        //}
    }
}
