#####################################################################
#
#   src/analysis/CMakeLists.txt
#
#   Build target for the analysis submodule.
#
#   Definitions:
#       toobad4ml::analysis (target | library)
#
#####################################################################

# Target definition
# -------------------------------------------------------------------

add_library(toobad4ml_analysis
    # sources
    ClangTool.cpp
    ModelBOFAction.cpp
    ModelBOFConsumer.cpp
    ModelBOFFrontendActionFactory.cpp
    # headers
    ClangTool.h
    ModelBOFAction.h
    ModelBOFConsumer.h
    ModelBOFFrontendActionFactory.h
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