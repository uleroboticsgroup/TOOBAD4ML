# ------------------------------------------------------------------------------
#
#   CMakeLists.txt - CMake file for the "analysis" module. This file
#                    provides the following target:
#
#                           * analysis
#
# ------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.1)

project(analysis)


# TARGET
# -----------------------------------------------------------------------------

add_library(${PROJECT_NAME}
    STATIC
        ClangTool.cpp
        ModelBOFAction.cpp
        ModelBOFConsumer.cpp
        ModelBOFFrontendActionFactory.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ASTTraversal
        description
        io
)
