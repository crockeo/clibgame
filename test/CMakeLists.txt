cmake_minimum_required(VERSION 2.8)
project(clibgame-test)

# Setting the output directories.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/bin")
SET(   LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/lib")

# Setting the C++11 flag.
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# Building the executable.
set(SOURCES src/rendering.cpp
            src/main.cpp)

add_executable(clibgame-test ${SOURCES})

# Finding all these packages.
find_package(clibgame REQUIRED)

# Include directories.
include_directories(${CLIBGAME_INCLUDE_DIRS})

# Libraries.
target_link_libraries(clibgame-test ${CLIBGAME_LIBRARIES})
