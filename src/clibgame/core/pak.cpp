#include "pak.hpp"

//////////////
// Includes //
#include <cstring>
#include <cstdlib>

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

        // Reading the headers in from the filesystem.
        void RealPak::readHeaders()
                throw(std::runtime_error) {
            if (fp == nullptr)
                throw std::runtime_error("Cannot read from null file pointer.");

            char header[4];
            fread(header, 1, 4, fp);
            if (strcmp(header, "CPAK") != 0)
                throw std::runtime_error("Invalid .pak file.");

            uint16_t items;
            fread(&items, 2, 1, fp);

            std::unordered_map<std::string, FileSpec> specs;
            std::string cppPath;
            char path[2048];
            uint32_t offset, length;
            for (int i = 0; i < items; i++) {
                char c = '\0';
                int j;
                for (j = 0; j < 2048 && c != '|'; j++) {
                    c = fgetc(fp);
                    path[j] = c;
                }
                path[j] = '\0';

                fread(&offset, 4, 1, fp);
                fread(&length, 4, 1, fp);

                cppPath = std::string(path);
                specs.insert(std::make_pair(cppPath, FileSpec {
                    cppPath, offset, length
                }));
            }
        }

        RealPak::RealPak(const char* path) {
            fp = fopen(path, "r");
            open = false;

            readHeaders();
        }

        RealPak::RealPak(std::string path) :
                RealPak(path.c_str()) { }

        RealPak::~RealPak() {
            fclose(fp);
        }

        // Constructing a new RealPak file to the 'outPath' from every file
        // listed in 'paths'.
        void RealPak::construct(std::string outPath, std::vector<std::string> paths)
                throw(std::runtime_error) {
            FILE* out = fopen(outPath.c_str(), "w");

            std::unordered_map<std::string, FileSpec> files;

            char *bytes = nullptr;
            int largest = -1;
            int len;
            for (std::string path: paths) {
                FILE* file = fopen(path.c_str(), "r");

                // Getting the file length.
                fseek(file, 0, SEEK_END);
                len = ftell(file);
                fseek(file, 0, SEEK_SET);

                if (len > largest) {
                    delete[] bytes;
                    bytes = new char[len];
                }

                fread(bytes, 1, len, file);
                fwrite(bytes, 1, len, out);
            }

            fclose(out);
        }

        // Validating that a .pak file at least *seems* to be structured
        // properly.
        bool RealPak::validate(std::string pakPath) {
            try {
                RealPak pak(pakPath);
                return true;
            } catch (std::runtime_error) {
                return false;
            }
        }

        // Checking if a given file exists within the Pak.
        bool RealPak::hasFile(std::string path) const {
            return files.find(path) != files.end();
        }

        // 'Opening' a file and providing a FILE pointer to is location.
        FILE* RealPak::openFile(std::string path, std::string options)
                throw(std::runtime_error, std::logic_error) {
            if (isOpen())
                throw std::logic_error("Cannot open a second file.");
            auto it = files.find(path);
            if (it == files.end())
                throw std::runtime_error("RealPak does not contain a file with that name.");
            fseek(fp, std::get<1>(*it).offset, SEEK_SET);
            return fp;
        }

        // Closing the currently-open file.
        void RealPak::closeFile()
                throw(std::logic_error) {
            if (!isOpen())
                throw std::logic_error("There is no open file to close.");
            fseek(fp, 0, SEEK_SET);
            open = false;
        }

        // Checking if a file is currently open.
        bool RealPak::isOpen() const {
            return open;
        }
    }
}
