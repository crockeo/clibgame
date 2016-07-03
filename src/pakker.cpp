#include "clibgame/core/pak.hpp"
#include <iostream>

// Printing help for the application.
void printHelp() {
    std::cout << "Proper usage:" << std::endl
              << "  pakker <mode> ..." << std::endl
              << std::endl
              << "  pakker validate <target_file.pak>" << std::endl
              << std::endl
              << "  pakker pak" << std::endl
              << "         <target_file.pak>" << std::endl
              << "         <source_file_1.xxx>" << std::endl
              << "     ... <source_file_n.xxx>" << std::endl
              << "  pakker open" << std::endl
              << "         <target_file.pak>" << std::endl
              << "         <pakked file name>" << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printHelp();
        return 1;
    }

    if (strcmp(argv[1], "validate") == 0) {
        std::cout << argv[2] << " is "
                  << (clibgame::core::RealPak::validate(argv[2]) ? "not " : "")
                  << "a valid .pak file." << std::endl;
    } else if (strcmp(argv[1], "pak") == 0) {
        std::vector<std::string> fromPaths;
        for (int i = 3; i < argc; i++)
            fromPaths.push_back(std::string(argv[i]));
        try {
            clibgame::core::RealPak::construct(argv[2], fromPaths);
        } catch (const std::runtime_error& e) {
            std::cerr << "!! FAILED TO CONSTRUCT PAK FILE !!" << std::endl
                      << "  " << e.what() << std::endl;
            return 1;
        }
    } else if (strcmp(argv[1], "open") == 0) {
        if (argc < 4) {
            printHelp();
            return 1;
        }

        clibgame::core::RealPak pak(argv[2]);
        clibgame::core::FileSpec info = pak.fileInfo(argv[3]);
        FILE *fp = pak.openFile(argv[3], "r");

        char *contents = new char[info.length];
        fread(contents, 1, info.length, fp);
        std::cout << "Contents: " << std::endl
                  << contents << std::endl;

        delete[] contents;
        pak.closeFile();
        
        return 0;
    } else {
        printHelp();
        return 1;
    }
}
