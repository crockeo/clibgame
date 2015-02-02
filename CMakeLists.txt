cmake_minimum_required(VERSION 2.8)
project(clibgame)

# Setting the output directories.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/bin")
set(LIBRARY_OUTPUT_PATH    "${PROJECT_SOURCE_DIR}/build/lib")

# Declaring the set of sources.
set(SOURCES
  src/clibgame/res/texture.cpp
)

# Adding this library.
add_library(clibgame ${SOURCES})

# Finding and setting up some packages.
find_package(glew REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})

target_link_libraries(clibgame ${GLEW_LIBRARY})
