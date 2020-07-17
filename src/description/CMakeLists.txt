#
#   CMakeLists.txt - CMake file for the TOOBAD4ML::description module. This
#                    file provides the following target:
#
#                           * description
#

cmake_minimum_required(VERSION 3.1)

project(description)


# Target
# -----------------------------------------------------------------------------

add_library(${PROJECT_NAME}
    SHARED
        BufferOverflow.cpp
        BufferOverflowBuilder.cpp
        CodePropertyGraph.cpp
        ExprUtils.cpp
        CPGExplorer.cpp
        MockDescriptor.cpp
        DescriptorDecorator.cpp
        SinkClassification.cpp
        CommandLine.cpp
        EnvironmentVariable.cpp
        File.cpp
        Network.cpp
        InputValidationClassification.cpp
        BufferSizePredicateClassification.cpp
        DataBufferDeclaration.cpp
        ArrayWriteIndexWithinBounds.cpp
        FormatStringPrecisionWithinBounds.cpp
        NumberOfElementsCopiedWithinBounds.cpp
        StringCopyWithinBounds.cpp
        DataDependentOnDestinationBufferSize.cpp
        DataDependentOnDestinationBufferSizeVariant.cpp
        IsCharacterCaseConversionSink.cpp
        ResetsInControlPredicates.cpp
        PadmanabhuniBuilder.cpp
        StringLengthSourceBuffer.cpp
        NULLCheck.cpp
        SizeSourceBuffer.cpp
        EOFCheck.cpp
        CharacterCheck.cpp
        CharacterOccurrenceStringCheck.cpp
        StringComparison.cpp
        SizeDestinationBuffer.cpp
        SizeDestinationBufferMinusOne.cpp
        SizeDestinationBufferMinusX.cpp
        StringLengthDestinationBuffer.cpp
        DescriptorFactory.cpp
        ContainerType.cpp
        IndexType.cpp
        LengthType.cpp
        AddressType.cpp
        PointerDeference.cpp
        MemoryAccess.cpp
        Container.cpp
        ViolatedBound.cpp
        DataType.cpp
        IndexComplexity.cpp
        LimitComplexity.cpp
        Magnitude.cpp
        DataSize.cpp
        ExploitCountermeasures.cpp
        HasDefensiveLimits.cpp
        SameSrcDstSize.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ASTTraversal
        LibTooling
)
