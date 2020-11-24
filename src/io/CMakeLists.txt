#####################################################################
#
#   src/io/CMakeLists.txt
#
#   Build target for the io submodule.
#
#   Definitions:
#       toobad4ml::io   (target | library)
#
#####################################################################

# Target definition
# -------------------------------------------------------------------

add_library(toobad4ml_io
    # sources
    FileManager.cpp
    FunctionTypeTranslator.cpp
    CSVOutputFormatStrategy.cpp
    STDOutputFormatStrategy.cpp
    CmdLineArguments.cpp
    FormatStrategyFactory.cpp
    InputManager.cpp
    Logger.cpp
    # headers
    FileManager.h
    FunctionTypeTranslator.h
    CSVOutputFormatStrategy.h
    STDOutputFormatStrategy.h
    CmdLineArguments.h
    FormatStrategyFactory.h
    InputManager.h
    Logger.h
)
add_library(toobad4ml::io ALIAS toobad4ml_io)

target_include_directories(toobad4ml_io
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>
)

target_link_libraries(toobad4ml_io
    PUBLIC
        ClangLibTooling
)