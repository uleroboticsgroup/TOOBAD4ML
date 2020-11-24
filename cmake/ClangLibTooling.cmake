#####################################################################
#
#   cmake/ClangLibTooling.cmake
#
#   Module for configuring Clang's LibTooling dependency.
#
#   Definitions:
#       ClangLibTooling (target | library)
#
#####################################################################

# Options
# -------------------------------------------------------------------

# LLVM avoids using C++ built in rtti, so we need to set the proper build
# flags (https://llvm.org/docs/HowToSetUpLLVMStyleRTTI.html)
set(CLANG_BUILD_FLAGS "-fno-rtti")

# list of imported targets in order to wrap the dependencies
set(CLANG_LIBTOOLING_IMPORTED_TARGETS "")

# Target definition
# -------------------------------------------------------------------

add_library(ClangLibTooling INTERFACE IMPORTED)

# step 1: import Clang (and thus LLVM) target from its dependency
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
    set(CLANGLIBTOOLING_IMPORTED_TARGETS clangTooling clangAST clangBasic)
else()
    message(STATUS "Using Clang dependency from Conan ...")

    find_package(libclang REQUIRED)

    set(CLANG_LIBTOOLING_IMPORTED_TARGETS libclang::libclang)
endif()

# step 2: configure our target by wrapping the imported one
target_compile_options(ClangLibTooling
    INTERFACE
        ${CLANG_BUILD_FLAGS}
)

target_link_libraries(ClangLibTooling
    INTERFACE
        ${CLANG_LIBTOOLING_IMPORTED_TARGETS}
)