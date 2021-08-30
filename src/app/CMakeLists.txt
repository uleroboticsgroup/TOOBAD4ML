#####################################################################
#
#   src/app/CMakeLists.txt
#
#   Main build target for the TOOBAD4ML CLI tool.
#
#   Definitions:
#       toobad4ml_exe   (target | executable)
#
#####################################################################

# Targets definition
# -------------------------------------------------------------------

# main build target
add_executable(toobad4ml_exe
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_link_libraries(toobad4ml_exe PUBLIC toobad4ml)