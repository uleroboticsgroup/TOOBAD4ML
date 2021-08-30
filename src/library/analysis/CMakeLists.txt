#####################################################################
#
#   src/library/analysis/CMakeLists.txt
#
#   Build target for the analysis submodule.
#
#   Definitions:
#       toobad4ml::analysis (target | library)
#
#####################################################################

# Target definition
# -------------------------------------------------------------------

add_library(toobad4ml_analysis
    OBJECT
        ${CMAKE_CURRENT_LIST_DIR}/ClangTool.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ClangTool.h
        ${CMAKE_CURRENT_LIST_DIR}/ModelBOFAction.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ModelBOFAction.h
        ${CMAKE_CURRENT_LIST_DIR}/ModelBOFConsumer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ModelBOFConsumer.h
        ${CMAKE_CURRENT_LIST_DIR}/ModelBOFFrontendActionFactory.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ModelBOFFrontendActionFactory.h
)
add_library(toobad4ml::analysis ALIAS toobad4ml_analysis)

target_include_directories(toobad4ml_analysis
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>
)

target_link_libraries(toobad4ml_analysis
    PUBLIC
        toobad4ml_asttraversal
        toobad4ml_description
        toobad4ml_io
    PRIVATE
        ClangLibTooling
)