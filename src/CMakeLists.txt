#
#   CMakeLists.txt - Script to build the source code
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

add_executable(main main.cpp)

target_link_libraries(main
    PRIVATE
        ${TOOBAD4ML_MODULES}
)
