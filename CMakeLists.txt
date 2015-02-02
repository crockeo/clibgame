cmake_minimum_required(VERSION 2.8)
project(clib-game)

# Setting the output directories.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/bin")
set(LIBRARY_OUTPUT_PATH    "${PROJECT_SOURCE_DIR}/build/lib")

# Declaring the set of sources.
set(SOURCES
  ""
)

# Adding this library.
add_library(clib-game ${SOURCES})
