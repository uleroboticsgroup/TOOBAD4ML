#####################################################################
#
#   tests/asttraversal/CMakeLists.txt
#
#   Sources definition related to the ASTTraversal module.
#
#####################################################################

target_sources(toobad4ml_tests
    PRIVATE
        #${CMAKE_CURRENT_LIST_DIR}/FindVariableVisitorTest.cpp
        #${CMAKE_CURRENT_LIST_DIR}/FindVariableVisitorTest.h
        ${CMAKE_CURRENT_LIST_DIR}/ExtractVulnerabilitesVisitorTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FindSelectedASTNodesVisitorTest.cpp
        #${CMAKE_CURRENT_LIST_DIR}/VisitorTest.cpp
        #${CMAKE_CURRENT_LIST_DIR}/VisitorTest.h
)

# Register the test for CMake
# -------------------------------------------------------------------

add_test(
    NAME    toobad4ml_asttraversal_test
    COMMAND toobad4ml_tests
)