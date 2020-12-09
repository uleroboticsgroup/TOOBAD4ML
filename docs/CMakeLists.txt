#####################################################################
#
#   doc/CMakeLists.txt
#
#   Build target for the TOOBAD4ML documentation.
#
#####################################################################

# Dependencies
# -------------------------------------------------------------------

find_package(Doxygen)

# Target definition
# -------------------------------------------------------------------

if (DOXYGEN_FOUND)

    set(DOXYGEN_IN  ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target(toobad4ml_api_doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Generating API documentation with Doxygen")

else (DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the API documentation")
endif (DOXYGEN_FOUND)