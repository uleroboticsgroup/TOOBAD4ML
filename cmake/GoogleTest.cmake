#####################################################################
#
#   cmake/GoogleTest.cmake
#
#   Module for configuring GoogleTest dependency.
#
#   Definitions:
#       GoogleTest (target | library)
#
#####################################################################

# Options
# -------------------------------------------------------------------

# list of imported targets in order to wrap the dependency
set (GOOGLETEST_IMPORTED_TARGETS "")

# Target definition
# -------------------------------------------------------------------

add_library (GoogleTest INTERFACE IMPORTED)

# step 1: import Google Test target from its dependency
if (TARGET CONAN_PKG::gtest)
    message (STATUS "Using Google Test dependency from Conan ...")
    set(GOOGLETEST_IMPORTED_TARGETS CONAN_PKG::gtest)
else ()
    find_package (GTest REQUIRED)
    message (STATUS "Found Google Test (v${GTEST_VERSION})")
    set (GOOGLETEST_IMPORTED_TARGETS GTest::GTest)
endif ()

# step 2: configure our target by wrapping the imported one
target_link_libraries (GoogleTest
    INTERFACE
        ${GOOGLETEST_IMPORTED_TARGETS}
)