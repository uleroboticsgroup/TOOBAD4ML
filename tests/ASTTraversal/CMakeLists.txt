cmake_minimum_required(VERSION 3.1)

project(ASTTraversal_test)


# Target
# -----------------------------------------------------------------------------

add_executable(${PROJECT_NAME}
    FindVariableVisitorTest.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ASTTraversal
        LibGoogleTest
)


# Register the test for CMake
# -----------------------------------------------------------------------------

add_test(
    NAME    ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)
