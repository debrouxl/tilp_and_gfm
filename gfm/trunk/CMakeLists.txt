cmake_minimum_required(VERSION 3.9)

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
pkg_check_modules(DEPS REQUIRED gtk+-2.0 libglade-2.0 glib-2.0 ticonv tifiles2 ticalcs2)

try_static_libs_if_needed()

# Defines
set(SHAREDIR  "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}")
target_compile_definitions(gfm PRIVATE PACKAGE="${PROJECT_NAME}" VERSION="${PROJECT_VERSION}" SHARE_DIR="${SHAREDIR}")

# CFLAGS and include dirs
target_compile_options(gfm PRIVATE ${DEPS_CFLAGS})

# Link-related properties, flags...
link_directories(${DEPS_LIBRARY_DIRS})
if(TRY_STATIC_LIBS)
    find_package(BZip2 REQUIRED) # Needed for some reason
    find_package(EXPAT REQUIRED) # Needed for some reason
    target_link_libraries(gfm ${BZIP2_LIBRARIES} ${EXPAT_LIBRARIES})
    target_link_libraries(gfm ${TRY_STATIC_DEPS_LDFLAGS})
    if(Iconv_FOUND AND NOT Iconv_IS_BUILT_IN)
        target_include_directories(gfm PRIVATE ${Iconv_INCLUDE_DIRS})
        target_link_libraries(gfm ${Iconv_LIBRARIES})
    endif()
else()
    string(REPLACE ";" " " DEPS_LDFLAGS "${DEPS_LDFLAGS}")
    target_link_libraries(gfm "${DEPS_LDFLAGS}" ${DEPS_LIBRARIES} ${Intl_LIBRARIES})
endif()

if(APPLE OR UNIX)
    set_target_properties(gfm PROPERTIES LINK_FLAGS "-rdynamic")  # rdynamic is needed for the GUI callback functions
endif()

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
