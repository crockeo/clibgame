# Findclibgame.cmake
#
# The script that helps you find your inner clibgame.

set(SEARCH_DIRECTORIES
  /usr/local
)

# Finding the clibgame header.
find_path(CLIBGAME_INCLUDE_DIRS clibgame.hpp
  PATH_SUFFIX include
  PATHS ${SEARCH_DIRECTORIES}
)

# Finding the clibgame library.
find_library(CLIBGAME_LIBRARY libclibgame.a
  PATH_SUFFIXES lib lib/static
  PATHS ${SEARCH_DIRECTORIES}
)

# Ensuring we found everything.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  CLIBGAME
  REQUIRED_VARS CLIBGAME_INCLUDE_DIRS CLIBGAME_LIBRARY
)
