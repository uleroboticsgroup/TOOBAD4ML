#
#   CMakeLists.txt - CMake file for the "description" module. This file
#                    provides the following target:
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
        CodePseudoPropertyGraph.cpp
        CPPGExplorer.cpp
        Descriptor.cpp
        FeatureExtractorDecorator.cpp
        SinkClassification.cpp
        SinkCharacteristicsClassification.cpp
        InputClassification.cpp
        InputValidationClassification.cpp
        BufferSizePredicateClassification.cpp
        PadmanabhuniBuilder.cpp
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
