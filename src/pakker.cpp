#include "clibgame/core/pak.hpp"
#include <iostream>

// Printing help for the application.
void printHelp() {
    std::cout << "Proper usage:" << std::endl
              << "  pakker <target_file.pak> <source_file_1.xxx> ... <source_file_n.xxx>" << std::endl;
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
        clibgame::core::constructPakFile(toPath, fromPaths);
    } catch (const std::runtime_error& e) {
        std::cerr << "!! FAILED TO CONSTRUCT PAK FILE !!" << std::endl
                  << "  " << e.what() << std::endl;
    }

    return 0;
}
