#
#   CMakeLists.txt - CMake file to build TOOBAD4ML. This file provides the
#                    following target:
#
#                            * TOOBAD4ML
#

# Dependencies
# -----------------------------------------------------------------------------

set(TOOBAD4ML_MODULES
    ASTTraversal
    description
    analysis
    io
)

foreach(MODULE IN LISTS TOOBAD4ML_MODULES)
    add_subdirectory(${MODULE})
endforeach()


# Target
# ----------------------------------------------------------------------------

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${TOOBAD4ML_MODULES}
)
