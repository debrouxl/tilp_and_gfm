cmake_minimum_required(VERSION 3.12)

project(tilp2
        VERSION     1.19
        LANGUAGES   C CXX)

file(GLOB HEADER_FILES src/*.h)
set(SRC_FILES
        ${HEADER_FILES}
        src/about.c
        src/action.c
        src/bookmark.c
        src/clist.c
        src/clist_rbm.c
        src/clock.c
        src/ctree.c
        src/ctree_rbm.c
        src/dboxes.c
        src/device.c
        src/dnd.c
        src/fileprop.c
        src/filesel.c
        src/gtk_gif.c
        src/gtk_update.c
        src/labels.c
        src/main.c
        src/manpage.c
        src/options.c
        src/pbars.c
        src/release.c
        src/screenshot.c
        src/scroptions.c
        src/splash.c
        src/support.c
        src/tilp.c
        src/tilp_calcs.c
        src/tilp_cmdline.c
        src/tilp_config.c
        src/tilp_device.c
        src/tilp_error.c
        src/tilp_files.c
        src/tilp_gif.c
        src/tilp_main.c
        src/tilp_misc.c
        src/tilp_paths.c
        src/tilp_screen.c
        src/tilp_slct.c
        src/tilp_update.c
        src/tilp_vars.c
        src/toolbar.c)

add_executable(tilp2 ${SRC_FILES})

if(WIN32)
    target_include_directories(tilp2 PRIVATE "build/msvc")
endif()

option(BUILD_USING_GTK3 "Build using GTK+3 instead of GTK+2" OFF)
if(BUILD_USING_GTK3)
    set(GTK_DEP "gtk+-3.0")
else()
    set(GTK_DEP "gtk+-2.0")
endif()

# External deps
pkg_check_modules(DEPS REQUIRED ${GTK_DEP} glib-2.0 ticonv tifiles2 ticables2 ticalcs2 zlib)
if(TRY_STATIC_LIBS AND WIN32)
    list(APPEND DEPS_LIBRARIES "libusb0")
    list(APPEND DEPS_STATIC_LIBRARIES "libusb0")
endif()

try_static_libs_if_needed()

# Defines
set(SHAREDIR  "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}")
target_compile_definitions(tilp2 PRIVATE PACKAGE="${PROJECT_NAME}" VERSION="${PROJECT_VERSION}" SHARE_DIR="${SHAREDIR}")

# CFLAGS
target_compile_options(tilp2 PRIVATE ${DEPS_CFLAGS})

# Link-related properties, flags...
if(TRY_STATIC_LIBS)
    target_compile_options(tilp2 PRIVATE ${DEPS_STATIC_CFLAGS})
    target_link_directories(tilp2 PRIVATE ${TRY_STATIC_DEPS_LIBSDIRS})
    target_link_libraries(tilp2 ${TRY_STATIC_DEPS_LDFLAGS_OTHER} ${TRY_STATIC_DEPS_LIBS})
    if(Iconv_FOUND AND NOT Iconv_IS_BUILT_IN)
        target_include_directories(tilp2 PRIVATE ${Iconv_INCLUDE_DIRS})
        if(Iconv_LIBRARY_DIRS)
            target_link_directories(tilp2 PRIVATE ${Iconv_LIBRARY_DIRS})
        endif()
        target_link_libraries(tilp2 ${Iconv_LIBRARIES})
    endif()
    if(LINUX)
        target_link_libraries(tilp2 ${CMAKE_DL_LIBS} -static-libgcc -static-libstdc++)
    endif()
    if(WIN32)
        target_link_options(tilp2 PRIVATE "/NODEFAULTLIB:LIBCMT.lib")
    endif()
else()
    target_compile_options(tilp2 PRIVATE ${DEPS_CFLAGS})
    target_link_directories(tilp2 PRIVATE ${DEPS_LIBRARY_DIRS})
    target_link_libraries(tilp2 ${DEPS_LDFLAGS_OTHER} ${DEPS_LIBRARIES})
endif()

if(APPLE OR UNIX)
    set_target_properties(tilp2 PROPERTIES LINK_FLAGS "-rdynamic")  # rdynamic is needed for the GUI callback functions
endif()

# Takes care of the i18n po/pot/gmo/mo files
if(ENABLE_NLS)
    i18n_mo_from_po_pot()
    if(TARGET potfiles_1)
        add_dependencies(tilp2 potfiles_1)
    else()
        message(WARNING "tilp2 target potfiles_1 (i18n) is not available - did you run intltool-update?")
        remove_definitions(-DENABLE_NLS)
    endif()
endif()

# .app bundle for macOS - disabled for now, we'll have to check how to make packaging better (see CPack?)
#set_target_properties(tilp2 PROPERTIES MACOSX_BUNDLE TRUE)

# The binary should not have the "2" suffix, to match other build systems.
set_target_properties(tilp2 PROPERTIES OUTPUT_NAME "tilp")

# Install rules
install(TARGETS tilp2
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        BUNDLE  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY   pixmaps help icons builder desktop
        DESTINATION "${SHAREDIR}")
install(FILES       man/tilp.1
        DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_MANDIR}/man1")
