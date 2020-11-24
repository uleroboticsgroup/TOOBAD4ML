#####################################################################
#
#   src/CMakeLists.txt
#
#   Main build target for the TOOBAD4ML tool.
#
#   Definitions:
#       toobad4ml   (target | executable)
#
#####################################################################

# Targets definition
# -------------------------------------------------------------------

# submodules targets
add_subdirectory(asttraversal)
add_subdirectory(description)
add_subdirectory(analysis)
add_subdirectory(io)

# main build target
add_executable(toobad4ml main.cpp)

target_link_libraries(toobad4ml
    toobad4ml_asttraversal
    toobad4ml_description
    toobad4ml_analysis
    toobad4ml_io
    ClangLibTooling
)