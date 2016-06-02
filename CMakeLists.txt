cmake_minimum_required(VERSION 2.8)
project(clibgame)

# Setting compiler flags.
set(CMAKE_CXX_FLAGS "-Wall -O2 -std=c++11 ${CMAKE_CXX_FLAGS}")

# Expanding the module path.
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Setting the output directories.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/bin")
set(LIBRARY_OUTPUT_PATH    "${PROJECT_SOURCE_DIR}/build/lib")

####
# Setting up required packages.

# Finding and setting up some packages.
find_package(freetype REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(PNG REQUIRED)

include_directories(
  ${FREETYPE_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  ${GLFW_INCLUDE_DIRS}
  ${PNG_INCLUDE_DIRS}
)

####
# Core clibgame Library.
#
# Consists of features used by multiple parts of the library. Abstracted out
# into core functionality.

set(CORE_HEADERS
  src/clibgame/core/debug.hpp
  src/clibgame/core/uuid.hpp
  src/clibgame/core/pak.hpp
  src/clibgame/core/all.hpp
)

set(CORE_SOURCES
  src/clibgame/core/debug.cpp
  src/clibgame/core/uuid.cpp
  src/clibgame/core/pak.cpp
)

add_library(clibgame-core SHARED ${CORE_SOURCES})

####
# Entity Components System.
#
# An entity component system. Solely dependent on the C++ standard library.

# Consists of a singular file, so I'm skipping that fancy mumbojumbo.
add_library(clibgame-ecs SHARED src/clibgame/ecs.cpp)

target_link_libraries(clibgame-ecs clibgame-core)

####
# Resource Loading Library.
#
# Functionality to manage loading different assets into the application. Handles
# the loading of textures, shaders, and sounds, as well as the organization of
# those files in blob files. Finally, it contains an asset manager which can
# parse asset specification files & precache them on startup.

set(RES_HEADERS
  src/clibgmae/res/texture.hpp
  src/clibgame/res/shader.hpp
  src/clibgame/res/sound.hpp
  src/clibgame/res/font.hpp
  src/clibgame/res/all.hpp
)

set(RES_SOURCES
  src/clibgame/res/texture.cpp
  src/clibgame/res/shader.cpp
  src/clibgame/res/sound.cpp
  src/clibgame/res/font.cpp
)

add_library(clibgame-res SHARED ${RES_SOURCES})

target_link_libraries(clibgame-res
  ${FREETYPE_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARY}
  ${GLFW_LIBRARY}
  ${PNG_LIBRARY}
)

####
# Pakker
#
# An application based on the Core library to construct and destruct .pak files.

add_executable(pakker src/pakker.cpp)

target_link_libraries(pakker clibgame-core)

####
# Installation Targets

# Declaring how we should install this.
#install(TARGETS clibgame
        #LIBRARY DESTINATION lib
        #ARCHIVE DESTINATION lib/static)

#install(DIRECTORY src/
        #DESTINATION include
        #FILES_MATCHING PATTERN *.hpp)

#install(FILES src/Findclibgame.cmake
        #DESTINATION "${CMAKE_ROOT}/Modules")
