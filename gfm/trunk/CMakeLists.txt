cmake_minimum_required(VERSION 3.5)

project(gfm
        VERSION     1.09
        LANGUAGES   C)

file(GLOB HEADER_FILES src/*.h)
set(SRC_FILES
        ${HEADER_FILES}
        src/cmdline.c
        src/ctree.c
        src/dialog.c
        src/file.c
        src/filesel.c
        src/gui.c
        src/labels.c
        src/main.c
        src/paths.c
        src/rwgroup.c
        src/splashscreen.c
        src/support.c
        src/tilibs.c
        src/ungroup.c)

add_executable(gfm ${SRC_FILES})

# External deps
pkg_check_modules(DEPS REQUIRED gtk+-2.0 glib-2.0 ticonv tifiles2 ticalcs2)
string(REPLACE ";" " " DEPS_LDFLAGS "${DEPS_LDFLAGS}")
find_package(Iconv REQUIRED)
find_package(GTK2 REQUIRED gtk glade)

# Defines
set(SHAREDIR  "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}")
target_compile_definitions(gfm PRIVATE PACKAGE="${PROJECT_NAME}" VERSION="${PROJECT_VERSION}" SHARE_DIR="${SHAREDIR}")

# CFLAGS and include dirs
target_compile_options(gfm PRIVATE ${DEPS_CFLAGS} ${GTK2_DEFINITIONS})
target_include_directories(gfm PRIVATE src ${GTK2_INCLUDE_DIRS})

# Link-related properties, flags...
link_directories(${DEPS_LIBRARY_DIRS})
target_link_libraries(gfm ${DEPS_LIBRARIES} ${GTK2_LIBRARIES} ${Iconv_LIBRARIES} ${Intl_LIBRARIES})
set_target_properties(gfm PROPERTIES LINK_FLAGS "${DEPS_LDFLAGS} -rdynamic")  # rdynamic is needed for the GUI callback functions

# Takes care of the i18n po/pot/gmo/mo files
i18n_mo_from_po_pot()
add_dependencies(gfm potfiles_1)

# .app bundle for macOS - disabled for now, we'll have to check how to make packaging better (see CPack?)
#set_target_properties(gfm PROPERTIES MACOSX_BUNDLE TRUE)

# Install rules
install(TARGETS gfm
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        BUNDLE  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY   pixmaps help icons glade desktop
        DESTINATION "${SHAREDIR}")
install(FILES       man/gfm.1
        DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_MANDIR}/man1")
