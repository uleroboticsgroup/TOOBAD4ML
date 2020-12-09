#####################################################################
#
#   tests/asttraversal/CMakeLists.txt
#
#   Sources definition related to the io module.
#
####################################################################

target_sources(toobad4ml_tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/LoggerTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CSVOutputFormatStrategyTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/STDOutputFormatStrategyTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FormatStrategyFactoryTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FileManagerTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/InputManagerTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CmdLineArgumentsTest.cpp
)

# Register the test for CMake
# -------------------------------------------------------------------

add_test(
    NAME    toobad4ml_io_test
    COMMAND toobad4ml_tests
)