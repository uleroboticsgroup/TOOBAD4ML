#####################################################################
#
#   tests/asttraversal/CMakeLists.txt
#
#   Sources definition related to the description module.
#
#####################################################################

target_sources(toobad4ml_tests
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ExprUtilsTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/IsCharacterCaseConversionSinkTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CommandLineTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/BufferOverflowTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CodePropertyGraphTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/BufferOverflowBuilderTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/StringLengthSourceBufferTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SinkClassificationTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/NumberOfElementsCopiedWithinBoundsTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ArrayWriteIndexWithinBoundsTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FormatStringPrecisionWithinBoundsTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/StringCopyWithinBoundsTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SizeSourceBufferTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/NULLCheckTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/EOFCheckTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CharacterCheckTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CharacterOccurrenceStringCheckTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/StringComparisonTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SizeDestinationBufferTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SizeDestinationBufferMinusOneTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SizeDestinationBufferMinusXTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/StringLengthDestinationBufferTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LengthTypeTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AddressTypeTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/IndexTypeTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ContainerTypeTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DescriptorFactoryTest.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CPGExplorerTest.cpp
)

# Register the test for CMake
# -------------------------------------------------------------------

add_test(
    NAME    toobad4ml_description_test
    COMMAND toobad4ml_tests
)
set_tests_properties(toobad4ml_description_test
    PROPERTIES
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)