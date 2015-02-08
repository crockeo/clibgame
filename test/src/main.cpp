//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <clibgame.hpp>

#include <iostream>

//////////
// Code //

#define UPDATES_PER_SECOND 120

// The entry point.
int main(int argc, char** argv) {
    if (!glfwInit()) {
        std::cerr << "Could not start GLFW." << std::endl;
        return 1;
    }

    // Creating the window.
    GLFWwindow* window = glfwCreateWindow(
        640, 480,
        "clibgame test",
        nullptr,
        nullptr
    );

    if (window == nullptr) {
        std::cerr << "Could not create window." << std::endl;
        glfwTerminate();
        return 1;
    }

    // Starting the game loop thingy?
    clibgame::Delta d;
    while (!glfwWindowShouldClose(window)) {
        float t = d.since();
        if (t < 1.f / UPDATES_PER_SECOND)
            clibgame::delayThread(1.f / UPDATES_PER_SECOND - t);

        glfwPollEvents();
    }

    // Closing up shop.
    glfwTerminate();
    return 0;
}
