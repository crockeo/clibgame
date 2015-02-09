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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    // Setting some OpenGL stuff.
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Could not initialize GLEW." << std::endl;
        glfwTerminate();
        return 1;
    }

    glClearColor(1.f, 0.f, 1.f, 1.f);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Starting the game loop thingy?
    clibgame::Delta d;
    while (!glfwWindowShouldClose(window)) {
        float t = d.since();
        if (t < 1.f / UPDATES_PER_SECOND)
            clibgame::delayThread(1.f / UPDATES_PER_SECOND - t);

        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: Something here?

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Closing up shop.
    glfwTerminate();
    return 0;
}
