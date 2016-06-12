// Name     : clibgame/core/pak.hpp
// Author(s): Cerek Hillen
// Init Date: 2016-05-31
// Edit Date: 2016-06-01
//
// Description:
//   Utilities around singular 'blob' files containing a set of other resource
//   files.

#ifndef _CLIBGAME_CORE_PAK_HPP_
#define _CLIBGAME_CORE_PAK_HPP_

//////////////
// Includes //
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>

//////////
// Code //

/*
 * So how do I want this to work? It would be convenient to have lil readers
 * that have a reference to the main one? How do I make sure that they're
 */

namespace clibgame {
    namespace core {
        // A unified Pak API which other Paks can implement.
        struct Pak {
            virtual ~Pak() { }

            // Checking if a given file exists within the Pak.
            virtual bool hasFile(std::string path) const = 0;

            // 'Opening' a file and providing a FILE pointer to is location.
            virtual FILE* openFile(std::string path, std::string options)
                    throw(std::runtime_error, std::logic_error) = 0;

            // Opening a file for non-binary reading.
            virtual FILE* openFile(std::string path) {
                return openFile(path, "r");
            }

            // Closing the currently-open file.
            virtual void closeFile()
                    throw(std::logic_error) = 0;

            // Checking if a file is currently open.
            virtual bool isOpen() const = 0;
        };

        // A Pak designed to emulate the functionality of a 'real' Pak by
        // providing an API directly to the filesystem instead.
        class FileSystemPak : public Pak {
        private:
            FILE* fp;
            bool open;

        public:
            FileSystemPak(const FileSystemPak&) = delete;
            FileSystemPak& operator=(const FileSystemPak&) = delete;

            FileSystemPak();

            ~FileSystemPak();
            
            // Checking if a given file exists within the Pak.
            virtual bool hasFile(std::string path) const;

            // 'Opening' a file and providing a FILE pointer to is location.
            virtual FILE* openFile(std::string path, std::string options)
                    throw(std::runtime_error, std::logic_error);

            // Closing the currently-open file.
            virtual void closeFile()
                    throw(std::logic_error);

            // Checking if a file is currently open.
            virtual bool isOpen() const;
        };

        // An organization of file data to be used when accessing information.
        struct FileSpec {
            std::string originalName;
            std::string path;
            int offset;
            int length;
        };

        // An API for opening files from a real Pak file.
        class RealPak : public Pak {
        private:
            std::unordered_map<std::string, FileSpec> files;
            FILE* fp;
            bool open;

            // Reading in from the std::ifstream to populate the files object.
            bool initFiles();

        public:
            RealPak(const RealPak&) = delete;
            RealPak& operator=(const RealPak&) = delete;            

            RealPak(const char* path);
            RealPak(std::string path);

            // Constructing a new RealPak file to the 'outPath' from every file
            // listed in 'paths'.
            static void construct(std::string outPath, std::vector<std::string> paths) throw(std::runtime_error);

            // Validating that a .pak file at least *seems* to be structured
            // properly.
            static bool validate(std::string pakPath);

            // Checking if a given file exists within the Pak.
            virtual bool hasFile(std::string path) const;

            // 'Opening' a file and providing a FILE pointer to is location.
            virtual FILE* openFile(std::string path, std::string options)
                    throw(std::runtime_error, std::logic_error);

            // Closing the currently-open file.
            virtual void closeFile()
                    throw(std::logic_error);

            // Checking if a file is currently open.
            virtual bool isOpen() const;
        };
    }
}

#endif
