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
        // The abstract definition of a Pak -- something that can provide a
        struct Pak {
            virtual ~Pak() { }

            // Opening a file and returning a std::ifstream& to its location.
            virtual std::istream& openFile(std::string path) throw(std::runtime_error, std::logic_error) = 0;

            // Closing a file -- should close the opened std::ifstream& if need
            // be.
            virtual void closeFile() throw(std::logic_error) = 0;

            // Checking if a file is open.
            virtual bool isOpen() const = 0;
        };

        // A Pak that's really just an API to open files from the filesystem.
        class FileSystemPak : public Pak {
        private:
            std::ifstream stream;
            bool open;

        public:
            FileSystemPak(const FileSystemPak&) = delete;
            FileSystemPak& operator=(const FileSystemPak&) = delete;

            FileSystemPak();

            ~FileSystemPak();
            
            // Opening a file and returning a std::ifstream& to its location.
            virtual std::istream& openFile(std::string path) throw(std::runtime_error, std::logic_error);

            // Closing a file -- should close the opened std::ifstream& if need
            // be.
            virtual void closeFile() throw(std::logic_error);

            // Checking if a file is open.
            virtual bool isOpen() const;
        };

        // An organization of file data to be used when accessing information.
        struct FileSpec {
            std::string originalName;
            std::string path;
            int offset;
            int length;
        };

        // A class that wraps around a std::istream to provide an artificial
        // length to the reader.
        class PakReader : public std::istream {
        private:
            std::istream& reader;
            int length;

        public:
            PakReader(const PakReader&) = delete;
            PakReader& operator=(const PakReader&) = delete;

            PakReader(std::istream& reader, int len);

            // Checking if the PakReader has ended.
            virtual bool eof() const;
        };

        // An API for opening files from a real Pak file.
        class RealPak : public Pak {
        private:
            std::unordered_map<std::string, FileSpec> files;
            std::ifstream reader;
            bool open;

            // Reading in from the std::ifstream to populate the files object.
            bool initFiles();

        public:
            RealPak(const RealPak&) = delete;
            RealPak& operator=(const RealPak&) = delete;            

            RealPak(std::string path);

            // Opening a file and returning a std::ifstream& to its location.
            virtual std::istream& openFile(std::string path) throw(std::logic_error);

            // Closing a file -- should close the opened std::ifstream& if need
            // be.
            virtual void closeFile() throw(std::logic_error);

            // Checking if a file is open.
            virtual bool isOpen() const;
        };

        // Constructing a PAK file from a vector of files on the filesystem.
        void constructPakFile(std::string outPath, std::vector<std::string> paths) throw(std::runtime_error);
    }
}

#endif
