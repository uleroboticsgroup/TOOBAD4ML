#
#   LibTooling.cmake - CMake module for configuring Clang's LibTooling
#                      dependency. This file provides the following target:
#
#                            * LibTooling
#
#   @author Gonzalo Esteban
#   @author Razvan Raducu
#   @author Flavio Rodrigues
#


# Options
# -----------------------------------------------------------------------------

# LLVM avoids using C++ built in rtti, so we need to set the proper build flags
# (https://llvm.org/docs/HowToSetUpLLVMStyleRTTI.html)
set(CLANG_BUILD_FLAGS "-fno-rtti")

# list of imported targets in order to wrap the dependencies
set(LIBTOOLING_IMPORTED_TARGETS "")


# LibTooling target
# -----------------------------------------------------------------------------

add_library(LibTooling INTERFACE)

# 1. import Clang (and thus LLVM) target from its dependency
if (NOT TOOBAD4ML_FORCE_CONAN)
    find_package(Clang)
endif()

if (Clang_FOUND)
    message(STATUS "Found LLVM and Clang (v ${LLVM_VERSION})")

    # if LLVM was built using rtti, disable the compile flag
    if(${LLVM_ENABLE_RTTI})
        set(CLANG_BUILD_FLAGS "")
    endif()

    # minimal clang targets used for LibTooling
    set(LIBTOOLING_IMPORTED_TARGETS clangTooling clangAST clangBasic)
else()
    message(STATUS "Using Clang dependency from Conan ...")

    find_package(clang REQUIRED)

    set(LIBTOOLING_IMPORTED_TARGETS clang::clang)
endif()

# 2. configure our target by wrapping the imported one
target_compile_options(LibTooling
    INTERFACE
        ${CLANG_BUILD_FLAGS}
)

target_link_libraries(LibTooling
    INTERFACE
        ${LIBTOOLING_IMPORTED_TARGETS}
)
