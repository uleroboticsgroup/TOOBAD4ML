#
#   CMakeLists.txt -
#

# Modules
# -----------------------------------------------------------------------------

include(GoogleTest)
#include(CTest)



# Targets
# -----------------------------------------------------------------------------

add_executable(test_main test_main.cpp)

target_link_libraries(test_main LibGoogleTest)



# Unit tests
# -----------------------------------------------------------------------------

set(TOOBAD4ML_MODULES
    analysis
    #ASTTraversal
)

foreach(MODULE IN LISTS TOOBAD4ML_MODULES)
    add_subdirectory(${MODULE})
endforeach()
