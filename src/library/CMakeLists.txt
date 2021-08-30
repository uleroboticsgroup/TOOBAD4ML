#####################################################################
#
#   src/library/CMakeLists.txt
#
#   Main build target for the TOOBAD4ML library.
#
#   Definitions:
#       toobad4ml   (target | library)
#
#####################################################################

# Targets definition
# -------------------------------------------------------------------

# submodules targets
add_subdirectory(ASTTraversal)
add_subdirectory(description)
add_subdirectory(analysis)
add_subdirectory(io)

# main build target
add_library(toobad4ml)

target_link_libraries(toobad4ml
    PUBLIC
        toobad4ml_asttraversal
        toobad4ml_description
        toobad4ml_analysis
        toobad4ml_io
        ClangLibTooling
)