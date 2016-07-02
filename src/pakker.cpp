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
              << "     ... <source_file_n.xxx>" << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printHelp();
        return 1;
    }

    std::string toPath = argv[1];
    std::vector<std::string> fromPaths;
    for (int i = 2; i < argc - 2; i++)
        fromPaths.push_back(std::string(argv[i]));

    try {
        clibgame::core::RealPak::construct(toPath, fromPaths);
    } catch (const std::runtime_error& e) {
        std::cerr << "!! FAILED TO CONSTRUCT PAK FILE !!" << std::endl
                  << "  " << e.what() << std::endl;
    }

    return 0;
}
