#####################################################################
#
#   src/library/asttraversal/CMakeLists.txt
#
#   Build target for the asttraversal submodule.
#
#   Definitions:
#       toobad4ml::astraversal  (target | library)
#
#####################################################################

# Target definition
# -------------------------------------------------------------------

add_library(toobad4ml_asttraversal
    OBJECT
        ${CMAKE_CURRENT_LIST_DIR}/ExtractVulnerabilitiesVisitor.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ExtractVulnerabilitiesVisitor.h
        ${CMAKE_CURRENT_LIST_DIR}/FindSelectedASTNodesVisitor.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FindSelectedASTNodesVisitor.h
        ${CMAKE_CURRENT_LIST_DIR}/FindVariableVisitor.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FindVariableVisitor.h
        ${CMAKE_CURRENT_LIST_DIR}/FindStmtVisitor.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FindStmtVisitor.h
)
add_library(toobad4ml::asttraversal ALIAS toobad4ml_asttraversal)

target_include_directories(toobad4ml_asttraversal
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>
)

target_link_libraries(toobad4ml_asttraversal
    PUBLIC
        ClangLibTooling
)