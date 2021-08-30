#####################################################################
#
#   src/CMakeLists.txt
#
#   Main CMake configuration script.
#
#####################################################################

# Project information
# -------------------------------------------------------------------

cmake_minimum_required (VERSION 3.1)

# name
set (PROJECT "toobad4ml")

# version
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)
set (VERSION_PATCH 0)
set (VERSION_CORE "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# description
set (DESCRIPTION "A tool for extracting characteristics of Buffer Overflow \
    vulnerabilities written in C code in order to further analyze them \
    with Machine Learning techniques")

project (${PROJECT}
    VERSION ${VERSION_CORE}
    DESCRIPTION ${DESCRIPTION}
    LANGUAGES CXX
)

# Project wide setup
# -------------------------------------------------------------------

# disable in-source builds
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message (FATAL_ERROR
        "This project does not allow in-source builds. Please remove "
        "CMakeCache.txt and CMakeFiles, then create a separate directory for "
        "the build files."
    )
endif()

# set a default build type
if (NOT CMAKE_BUILD_TYPE)
    message (STATUS
        "Setting build type as 'Debug' as none was specified"
    )
    set (CMAKE_BUILD_TYPE Debug
         CACHE STRING "Default build type set to Debug" FORCE
    )
endif()

# additional modules
list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# user options
option (TOOBAD4ML_ENABLE_TESTING "Build unit tests" OFF)
option (TOOBAD4ML_GENERATE_DOCS  "Build documentation" OFF)

# Dependencies
# -------------------------------------------------------------------

include (ClangLibTooling)

# Main build targets
# -------------------------------------------------------------------

# source code (library + CLI tool)
add_subdirectory (library)
add_subdirectory (app)

# unit tests
if (TOOBAD4ML_ENABLE_TESTING)
    add_subdirectory (tests)
endif (TOOBAD4ML_ENABLE_TESTING)

# documentation
if (TOOBAD4ML_GENERATE_DOCS)
    add_subdirectory ("${CMAKE_SOURCE_DIR}/docs" "${CMAKE_BINARY_DIR}/docs")
endif (TOOBAD4ML_GENERATE_DOCS)