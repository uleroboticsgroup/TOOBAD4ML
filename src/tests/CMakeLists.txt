#####################################################################
#
#   tests/CMakeLists.txt
#
#   Main build target for the TOOBAD4ML unit tests.
#
#   Definitions:
#       toobad4ml_tests   (target | executable)
#
#####################################################################

# Dependencies
# -------------------------------------------------------------------

include (GoogleTest)
include (CTest)

# Target definition
# -------------------------------------------------------------------

# main build target
add_executable (toobad4ml_tests
    ${CMAKE_CURRENT_LIST_DIR}/test_main.cpp
)
add_subdirectory (ASTTraversal)
add_subdirectory (analysis)
add_subdirectory (description)
add_subdirectory (io)

target_include_directories (toobad4ml_tests
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_link_libraries (toobad4ml_tests
    PRIVATE
        toobad4ml::asttraversal
        toobad4ml::analysis
        toobad4ml::description
        toobad4ml::io
        GoogleTest
)

# Code coverage (with gcovr)
# -------------------------------------------------------------------

if (CMAKE_COMPILER_IS_GNUCXX)
    include (CodeCoverage)
    append_coverage_compiler_flags ()
    setup_target_for_coverage_gcovr_xml (
        NAME coverage
        EXECUTABLE toobad4ml_tests
    )
endif ()