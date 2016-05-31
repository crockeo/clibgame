cmake_minimum_required(VERSION 2.8)
project(clibgame)

# Setting compiler flags.
set(CMAKE_CXX_FLAGS "-Wall -O2 -std=c++11 ${CMAKE_CXX_FLAGS}")

# Expanding the module path.
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Setting the output directories.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/bin")
set(LIBRARY_OUTPUT_PATH    "${PROJECT_SOURCE_DIR}/build/lib")

# Finding and setting up some packages.
#find_package(freetype REQUIRED)
#find_package(parsical REQUIRED)
#find_package(GLEW REQUIRED)
#find_package(GLFW REQUIRED)
#find_package(PNG REQUIRED)

####
# Primary Core Library (will be split up later).

# Declaring the set of sources.
#set(SOURCES
  #src/clibgame/components/position.cpp
  #src/clibgame/res/animation.cpp
  #src/clibgame/res/texsheet.cpp
  #src/clibgame/engineconfig.cpp
  #src/clibgame/res/texture.cpp
  #src/clibgame/res/shader.cpp
  #src/clibgame/res/font.cpp
  #src/clibgame/eventing.cpp
  #src/clibgame/engine.cpp
  #src/clibgame/delta.cpp
  #src/clibgame/timer.cpp
  #src/clibgame/ecp.cpp
  #src/clibgame/res.cpp
#)

# Adding this library.
#add_library(clibgame STATIC ${SOURCES})

#include_directories(${FREETYPE_INCLUDE_DIRS}
                    #${PARSICAL_INCLUDE_DIRS}
                    #${GLEW_INCLUDE_DIRS}
                    #${GLFW_INCLUDE_DIRS}
                    #${PNG_INCLUDE_DIRS})

#target_link_libraries(clibgame ${FREETYPE_LIBRARIES}
                               #${PARSICAL_LIBRARIES}
                               #${GLEW_LIBRARY}
                               #${GLFW_LIBRARY}
                               #${PNG_LIBRARY})

####
# The *Real* Core clibgame Library.
#
# Consists of features used by multiple parts of the library. Abstracted out
# into core functionality.

set(CORE_HEADERS
  src/clibgame/core/debug.hpp
  src/clibgame/core/uuid.hpp
)

set(CORE_SOURCES
  src/clibgame/core/debug.cpp
  src/clibgame/core/uuid.cpp
)

add_library(clibgame-core SHARED ${CORE_SOURCES})

####
# The Entity Components System.
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

set(RESOURCE_HEADERS
  src/clibgame/resource/manager.cpp
  src/clibgmae/resource/texture.hpp
  src/clibgame/resource/shader.hpp
  src/clibgame/resource/sound.hpp
  src/clibgame/resource/pak.hpp
  src/clibgame/resource.hpp
)

set(RESOURCE_SOURCES
  src/clibgame/resource/manager.cpp
  src/clibgame/resource/texture.cpp
  src/clibgame/resource/shader.cpp
  src/clibgame/resource/sound.cpp
  src/clibgame/resource/pak.cpp
)

#add_library(clibgame-resource SHARED ${RESOURCE_SOURCES})

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
