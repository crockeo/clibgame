# Name: Findclibgame.cmake
#
# Description:
#   This cmake file is used to find clibgame and its dependencies on a
#   filesystem and declare the ${CLIBGAME_LIBRARIES} & ${CLIBGAME_INCLUDE_DIRS}
#   variables respectively.
#

# Setting the set of search directories.
set(SEARCH_DIRECTORIES
  /usr/local
)

# Finding the clibgame headers.
find_path(CLIBGAME_INCLUDE_DIR clibgame.hpp
  PATH_SUFFIX include
  PATHS ${SEARCH_DIRECTORIES}
)

# Finding the clibgame library.
find_library(CLIBGAME_LIBRARY
  NAMES clibgame
  PATH_SUFFIXES lib lib/static
  PATHS ${SEARCH_DIRECTORIES}
)

# Finding dependencies and stuff.
find_package(freetype REQUIRED)
find_package(parsical REQUIRED)
find_package(opengl REQUIRED)
find_package(glew REQUIRED)
find_package(glfw REQUIRED)
find_package(png REQUIRED)

set(CLIBGAME_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIRS}
                          ${PARSICAL_INCLUDE_DIRS}
                          ${CLIBGAME_INCLUDE_DIR}
                          ${OPENGL_INCLUDE_DIRS}
                          ${GLEW_INCLUDE_DIRS}
                          ${GLFW_INCLUDE_DIRS}
                          ${PNG_INCLUDE_DIRS})

set(CLIBGAME_LIBRARIES ${FREETYPE_LIBRARIES}
                       ${PARSICAL_LIBRARIES}
                       ${CLIBGAME_LIBRARY}
                       ${OPENGL_LIBRARY}
                       ${GLEW_LIBRARY}
                       ${GLFW_LIBRARY}
                       ${PNG_LIBRARY})

# Making sure that we found everything.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  CLIBGAME
  REQUIRED_VARS CLIBGAME_INCLUDE_DIR CLIBGAME_LIBRARY
)
