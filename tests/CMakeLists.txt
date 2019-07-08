#
#   CMakeLists.txt - CMake file to build unit tests for TOOBAD4ML. This file
#                    provides the following target:
#
#                           * tests
#


# Modules
# -----------------------------------------------------------------------------

include(GoogleTest)


# Test suites
# -----------------------------------------------------------------------------

# TODO add test suites for each module
set(TOOBAD4ML_TEST_SUITES
    analysis
    ASTTraversal
    description
    io
)

foreach(TEST_SUITE IN LISTS TOOBAD4ML_TEST_SUITES)
    add_subdirectory(${TEST_SUITE})
endforeach()


# Target
# -----------------------------------------------------------------------------

add_executable(tests test_main.cpp)

target_link_libraries(tests
    PUBLIC
        gtest_main
        gmock
)
