#include "engine.hpp"

//////////////
// Includes //
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "delta.hpp"

//////////
// Code //

namespace clibgame {
    // The primary engine loop.
    void engineLoop(GLFWwindow* window, EngineConfig cfg, ECP& ecp, const Res& resources) {
        const int dps = cfg.ups >= cfg.rps ? cfg.ups : cfg.rps;
        Delta rDelta, uDelta;
        float rTime = 0.f,
              uTime = 0.f;

        while (!glfwWindowShouldClose(window)) {
            if (uTime > 1.f / cfg.ups) {
                ecp.updateEntities(window, uTime);
                uTime = 0.f;
            }

            if (rTime > 1.f / cfg.rps) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                ecp.renderEntities();
                glfwSwapBuffers(window);

                rTime = 0.f;
            }

            rTime += rDelta.since();
            uTime += uDelta.since();

            clibgame::delayThread(1.f / dps);
            glfwPollEvents();
        }
    }
}

// Starting the engine from an ECP derivative and the location of a set of
// resources.
void clibgame::startEngine(EngineConfig cfg, ECP& ecp, std::string path) throw(std::runtime_error) {
    // Initializing GLFW.
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW.");

    // Grabbing the monitor.
    GLFWmonitor* monitor = cfg.fullscreen ? glfwGetPrimaryMonitor() : nullptr;
    if (cfg.fullscreen && monitor == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to access the primary monitor.");
    }

    // Setting window hints.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Opening a window.
    GLFWwindow* window = glfwCreateWindow(
        cfg.width, cfg.height,
        cfg.title.c_str(),
        monitor,
        nullptr
    );

    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create the window.");
    }

    // Setting up GLEW and OpenGL.
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLEW.");
    }

    glClearColor(1.f, 0.f, 1.f, 1.f);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Loading resources.
    Res resources;

    try {
        clibgame::loadRes(resources, path);
    } catch (std::runtime_error& e) {
        throw e;
    }

    ecp.initEntities(window, resources);

    // Starting the update threads.
    clibgame::engineLoop(window, cfg, ecp, resources);

    // Cleaning up.
    glfwTerminate();
}
