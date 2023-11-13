cmake_minimum_required(VERSION 3.9)

project(tilp_and_gfm C)

##################################
# CMake support for tilp and gfm #
##################################
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
# Notes:
#   - this has been succesfully tested on recent macOS and Linux.
#   - The TRY_STATIC_LIBS CMake option will try to build both executables using as many static dependent libraries as possible.
#     This would be particularly useful if you also built the tilibs with TRY_STATIC_LIBS as well.
#     Let's note however that there is currently not much advantage in building that way, using shared libs is preferred, but
#     at least you have the choice to do whatever you want should you ever really need a static build.
#
# In the future...:
#   - TODO: look at CPack features for bundling/packaging
#   - WISH: do not hardcode the (auto-generated...) potfiles_* target names
#   - WISH: add support for Windows (that will probably be annoying)
#

message(STATUS "Detected system: ${CMAKE_SYSTEM_NAME} - host processor: ${CMAKE_HOST_SYSTEM_PROCESSOR}")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

option(TRY_STATIC_LIBS "Build using as many static libs as possible" OFF)
if(TRY_STATIC_LIBS)
    if(WIN32)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
    else()
        set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
    endif()
endif()

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

# Set RPath on macOS, this is somehow needed now?
if(APPLE)
    set(CMAKE_MACOSX_RPATH 1)
    list(APPEND CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
endif()

add_subdirectory(tilp/trunk)

# libglade isn't available (anymore) on brew or on vcpkg... so let's check that here
pkg_check_modules(TEST_GLADE libglade-2.0)
if(TEST_GLADE_FOUND)
    add_subdirectory(gfm/trunk)
else()
    message(WARNING "libglade is not available on your system, gfm will not be built")
endif()
