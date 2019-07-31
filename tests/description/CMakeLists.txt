cmake_minimum_required(VERSION 3.1)

project(description_test)

# Target
# -----------------------------------------------------------------------------

add_executable(${PROJECT_NAME}
    ExprUtilsTest.cpp
    IsCharacterCaseConversionSinkTest.cpp
    CommandLineTest.cpp
    BufferOverflowTest.cpp
    CodePropertyGraphTest.cpp
    BufferOverflowBuilderTest.cpp
    StringLengthSourceBufferTest.cpp
    SinkClassificationTest.cpp
    NumberOfElementsCopiedWithinBoundsTest.cpp
    ArrayWriteIndexWithinBoundsTest.cpp
    FormatStringPrecisionWithinBoundsTest.cpp
    StringCopyWithinBoundsTest.cpp
    CPGExplorerTest.cpp
)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    	description
        LibGoogleTest
)

# TODO we temporary need this to link the test main with the test suites
set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS 1)

# Register the test for CMake
# -----------------------------------------------------------------------------

add_test(
    NAME    ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)
