#####################################################################
#
#   CMakeLists.txt
#
#   CMake configuration script for wrapping Conan dependencies.
#
#####################################################################

cmake_minimum_required (VERSION 3.1)

project (toobad4ml_conan_wrapper)

# conan dependencies
include ("conanbuildinfo.cmake"
    RESULT_VARIABLE TOOBAD4ML_CONAN_FOUND
    OPTIONAL
)
if (NOT TOOBAD4ML_CONAN_FOUND)
    include ("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake"
        RESULT_VARIABLE TOOBAD4ML_CONAN_FOUND
        OPTIONAL
    )
endif(NOT TOOBAD4ML_CONAN_FOUND)

if (TOOBAD4ML_CONAN_FOUND)
    message (STATUS "Conan found! Setting it up...")
    conan_basic_setup (TARGETS)
endif (TOOBAD4ML_CONAN_FOUND)

# add support for testing
enable_testing ()

# source code
add_subdirectory (src)