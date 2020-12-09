#####################################################################
#
#   tests/analysis/CMakeLists.txt
#
#   Sources definition related to the analysis module.
#
#####################################################################

target_sources(toobad4ml_tests
    PRIVATE
        # sources
        ${CMAKE_CURRENT_LIST_DIR}/ModelBOFActionTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ModelBOFConsumerTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ModelBOFFrontendActionFactoryTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ClangToolTest.cpp
        # headers
        ${CMAKE_CURRENT_LIST_DIR}/ModelBOFActionTestHelper.h
)

# Register the test for CMake
# -------------------------------------------------------------------

add_test(
    NAME    toobad4ml_analysis_test
    COMMAND toobad4ml_tests
)