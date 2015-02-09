cmake_minimum_required(VERSION 2.8)
project(clibgame-test)

# Finding local cmake files.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# Setting the output directories.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/bin")
SET(   LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/lib")

# Setting the C++11 flag.
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# Building the executable.
set(SOURCES src/main.cpp)

add_executable(clibgame-test ${SOURCES})

# Finding all these packages.
find_package(clibgame REQUIRED)
find_package(opengl REQUIRED)
find_package(glew REQUIRED)
find_package(glfw REQUIRED)

# Include directories.
include_directories(${CLIBGAME_INCLUDE_DIRS}
                    ${OPENGL_INCLUDE_DIRS}
                    ${GLEW_INCLUDE_DIRS}
                    ${GLFW_INCLUDE_DIRS})

# Libraries.
target_link_libraries(clibgame-test ${CLIBGAME_LIBRARY}
                                    ${OPENGL_LIBRARY}
                                    ${GLEW_LIBRARY}
                                    ${GLFW_LIBRARY})
