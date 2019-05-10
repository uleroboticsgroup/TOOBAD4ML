#
#   CMakeLists.txt - CMake file for the "ASTTraversal" module. This file
#                    provides the following target:
#
#                           * ASTTraversal
#

cmake_minimum_required(VERSION 3.1)

project(ASTTraversal)


# Target
# -----------------------------------------------------------------------------

add_library(${PROJECT_NAME}
    SHARED
        ExtractVulnerabilitiesVisitor.cpp
        FindSelectedASTNodesVisitor.cpp
        FindVariableVisitor.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        LibTooling
)
