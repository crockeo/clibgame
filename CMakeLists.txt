cmake_minimum_required(VERSION 2.8)
project(clibgame)

# Setting compiler flags.
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# Setting the output directories.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/bin")
set(LIBRARY_OUTPUT_PATH    "${PROJECT_SOURCE_DIR}/build/lib")

# Declaring the set of sources.
set(SOURCES
  src/clibgame/res/animation.cpp
  src/clibgame/res/texsheet.cpp
  src/clibgame/res/texture.cpp
  src/clibgame/res/shader.cpp
  src/clibgame/eventing.cpp
  src/clibgame/engine.cpp
  src/clibgame/delta.cpp
  src/clibgame/timer.cpp
  src/clibgame/ecp.cpp
  src/clibgame/res.cpp
)

# Adding this library.
add_library(clibgame STATIC ${SOURCES})

# Finding and setting up some packages.
find_package(glew REQUIRED)
find_package(png REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS}
                    ${PNG_INCLUDE_DIRS})

target_link_libraries(clibgame ${GLEW_LIBRARY}
                               ${PNG_LIBRARY})

# Declaring how we should install this.
install(TARGETS clibgame
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)

install(DIRECTORY src/
        DESTINATION include
        FILES_MATCHING PATTERN *.hpp)
