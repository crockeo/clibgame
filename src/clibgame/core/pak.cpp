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
                throw(std::runtime_error, std::logic_error) {
            // Opening the series of files to use in the rest of this
            // application.
            std::vector<FILE *> files;
            for (std::string path: paths) {
                if (path.size() > 2047) {
                    for (FILE *opened: files)
                        fclose(opened);
                    throw std::runtime_error("Path size is too long '" + path + "'.");
                }

                FILE *f = fopen(path.c_str(), "r");
                if (f == nullptr) {
                    for (FILE *opened: files)
                        fclose(opened);
                    throw std::runtime_error("Failed to open file '" + path + "'.");
                }

                files.push_back(f);
            }

            // Writing out header information.
            FILE *out = fopen(outPath.c_str(), "w");
            fprintf(out, "CPAK");
            uint32_t offset = 0;
            uint32_t length;
            for (FILE *f: files) {
                fseek(f, 0, SEEK_END);
                length = ftell(f);
                fseek(f, 0, SEEK_SET);

                fwrite(&offset, 4, 1, out);
                fwrite(&length, 4, 1, out);

                offset += length;
            }

            // Writing out the files themselves.
            uint32_t contentsLength = 0;
            length = 0;
            char *contents = nullptr;
            for (FILE *f: files) {
                fseek(f, 0, SEEK_END);
                length = ftell(f);
                fseek(f, 0, SEEK_SET);

                if (length > contentsLength) {
                    contentsLength = length;
                    if (contents != nullptr)
                        delete[] contents;
                    contents = new char[contentsLength];
                }

                fread(contents, 1, length, f);
                fwrite(contents, 1, length, out);
                fclose(f);
            }

            if (contents != nullptr)
                delete[] contents;
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

        // Getting file info from a contained file.
        FileSpec RealPak::fileInfo(std::string path) const
                throw(std::logic_error) {
            if (!hasFile(path))
                throw std::logic_error("Pak does not contain " + path + ".");
            return files.at(path);
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
