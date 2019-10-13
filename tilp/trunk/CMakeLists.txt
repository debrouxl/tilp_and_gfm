cmake_minimum_required(VERSION 3.5)

project(tilp2
        VERSION     1.19
        LANGUAGES   C)

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

option(BUILD_USING_GTK3 "Build using GTK+3 instead of GTK+2" OFF)
if(BUILD_USING_GTK3)
    set(GTK_DEP "gtk+-3.0")
else()
    set(GTK_DEP "gtk+-2.0")
endif()

# External deps
pkg_check_modules(DEPS REQUIRED ${GTK_DEP} glib-2.0 ticonv tifiles2 ticables2 ticalcs2 zlib)
string(REPLACE ";" " " DEPS_LDFLAGS "${DEPS_LDFLAGS}")
find_package(Iconv REQUIRED)

# Defines
set(SHAREDIR  "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}")
target_compile_definitions(tilp2 PRIVATE PACKAGE="${PROJECT_NAME}" VERSION="${PROJECT_VERSION}" SHARE_DIR="${SHAREDIR}")

# CFLAGS
target_compile_options(tilp2 PRIVATE ${DEPS_CFLAGS})

# Link-related properties, flags...
link_directories(${DEPS_LIBRARY_DIRS})
target_link_libraries(tilp2 ${DEPS_LIBRARIES} ${Iconv_LIBRARIES} ${Intl_LIBRARIES})
set_target_properties(tilp2 PROPERTIES LINK_FLAGS "${DEPS_LDFLAGS} -rdynamic")  # rdynamic is needed for the GUI callback functions

# Takes care of the i18n po/pot/gmo/mo files
i18n_mo_from_po_pot()
add_dependencies(tilp2 potfiles_2)

# .app bundle for macOS - disabled for now, we'll have to check how to make packaging better (see CPack?)
#set_target_properties(tilp2 PROPERTIES MACOSX_BUNDLE TRUE)

# Install rules
install(TARGETS tilp2
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        BUNDLE  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY   pixmaps help icons builder desktop
        DESTINATION "${SHAREDIR}")
install(FILES       man/tilp.1
        DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_MANDIR}/man1")
