#
#   GoogleTest.cmake - CMake script for configuring GoogleTest dependency. This
#                      file provides the following target:
#
#                             * GoogleTest
#
#   @author Gonzalo Esteban
#   @author Razvan Raducu
#   @author Flavio Rodrigues
#


# Options
# -----------------------------------------------------------------------------

# list of imported targets in order to wrap the dependencies
set(GOOGLETEST_IMPORTED_TARGETS "")

# enable CMake support for tests
enable_testing()


# GoogleTest target
# -----------------------------------------------------------------------------

add_library(LibGoogleTest INTERFACE)

# 1. import Google Test target from its dependency
if (NOT TOOBAD4ML_FORCE_CONAN)
    find_package(GTest)
endif()

if (GTEST_FOUND)
    message(STATUS "Found Google Test (v ${GTEST_VERSION})")

    # TODO Since gtest 1.8.0, gtest and gmock are integrated. CMake 3.10+
    # supports this, so for lower versions we must implement some workaround...
    set(GOOGLETEST_IMPORTED_TARGETS GTest::GTest GTest::Main)
else()
    message(STATUS "Using Google Test dependency from Conan ...")

    find_package(gtest REQUIRED)

    set(GOOGLETEST_IMPORTED_TARGETS gtest::gtest)
endif()

# 2. configure our target by wrapping the imported one
target_link_libraries(LibGoogleTest
    INTERFACE
        ${GOOGLETEST_IMPORTED_TARGETS}
)
