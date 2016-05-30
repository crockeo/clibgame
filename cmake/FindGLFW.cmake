# Name  : FindGLFW.cmake
# Author: Cerek Hillen
#
# Description:
#   A cmake file to locate headers & library files for OpenGL.

# Finding the include directories.
find_path(GLFW_INCLUDE_DIRS GLFW/glfw3.h
  PATHS /usr/local/include
        /usr/X11/include
        /usr/include
        /opt/local/include
)

# Finding the libraries.
find_library(GLFW_LIBRARIES
  NAMES glfw glfw3
  PATHS /usr/local
        /usr/X11
        /usr
  PATH_SUFFIXES lib64
                lib
                a
)

# Making sure we have GLFW.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLFW REQUIRED_VARS GLFW_INCLUDE_DIRS
                                                     GLFW_LIBRARIES)
