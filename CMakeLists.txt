cmake_minimum_required(VERSION 3.5)

project(tilp_and_gfm C)

###############################################
# Experimental CMake support for tilp and gfm #
###############################################
#
# This aims to provide a much simpler way to build and install tilp and gfm
# on computers that have decent and recent OS and toolchains.
# As a bonus, it provides better support for CMake-oriented IDE (e.g. CLion).
#
# Features:
#   - builds and installs both executables
#   - creates and installs i18n .mo files (when libs/tools are present)
#
# Caveats:
#   - you'll need to generate the pot files first (intltool-update --pot)
#   - not all the autotools/configure options are available
#   - probably doesn't work very well with ancient toolchains or on uncommon OSes
#
# In the future...:
#   - TODO: look at CPack features for bundling/packaging
#   - WISH: do not hardcode the (auto-generated...) potfiles_* target names
#   - WISH: make Travis try the cmake-based build too
#   - WISH: add support for Windows (that will probably be annoying)
#

message(STATUS "Detected system: ${CMAKE_SYSTEM_NAME} - host processor: ${CMAKE_HOST_SYSTEM_PROCESSOR}")

include(GNUInstallDirs)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -Wextra -Wno-unused-parameter -Werror=shadow -Werror=write-strings -Wredundant-decls -Werror=format -Werror=format-nonliteral -Werror=format-security -Werror=declaration-after-statement -Werror=implicit-function-declaration -Werror=date-time -Werror=missing-prototypes -Werror=return-type -Werror=pointer-arith ")

if(APPLE)
    add_definitions(-D__MACOSX__)
elseif(UNIX)
    add_definitions(-D__LINUX__)
elseif(MINGW)
    add_definitions(-D__MINGW32__)
elseif(WIN32)
    add_definitions(-D__WIN32__)
endif()

# i18n support checking
include(FindGettext)
include(FindIntl)
if(Intl_FOUND AND GETTEXT_FOUND)
    set(ENABLE_NLS 1)
    add_definitions(-DENABLE_NLS=1)
else()
    message(WARNING "The Intl and GetText libs are needed for translations - English only will be available")
endif()
set(LOCALEDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LOCALEDIR}")

# Global defines
add_definitions(-DENABLE_LOGGING=1 -DHAVE_FVISIBILITY=1 -DLOCALEDIR="${LOCALEDIR}")

# For libs finding
find_package(PkgConfig)

# Our modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/.cmake)
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/.cmake/*.cmake")
foreach(file ${files})
    include(${file})
endforeach()

add_subdirectory(gfm/trunk)
add_subdirectory(tilp/trunk)
