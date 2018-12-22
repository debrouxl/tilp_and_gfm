function(i18n_mo_from_po_pot)
    if(ENABLE_NLS)
        # Fetch pot file name
        file(GLOB POTFILE ${CMAKE_CURRENT_SOURCE_DIR}/po/*.pot)
        if(POTFILE)
            list(GET POTFILE 0 POTFILE)
            get_filename_component(POTNAME ${POTFILE} NAME_WE)
            # Fetch po files names
            file(GLOB PO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/po/*.po)
            set(LANGS "")
            # Process all...
            foreach(PO_FILE ${PO_FILES})
                get_filename_component(lang ${PO_FILE} NAME_WE)
                list(APPEND LANGS ${lang})
                configure_file(${PO_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${lang}.po COPYONLY)
            endforeach()
            gettext_process_pot_file(${CMAKE_CURRENT_SOURCE_DIR}/po/${POTNAME}.pot ALL
                INSTALL_DESTINATION ${LOCALEDIR}
                LANGUAGES           ${LANGS})
        endif()
    endif()
endfunction()
