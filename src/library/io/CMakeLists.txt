#####################################################################
#
#   src/io/CMakeLists.txt
#
#   Build target for the io submodule.
#
#   Definitions:
#       toobad4ml::io   (target | library)
#
#####################################################################

# Target definition
# -------------------------------------------------------------------

add_library(toobad4ml_io
    OBJECT
        ${CMAKE_CURRENT_LIST_DIR}/FileManager.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FileManager.h
        ${CMAKE_CURRENT_LIST_DIR}/FunctionTypeTranslator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FunctionTypeTranslator.h
        ${CMAKE_CURRENT_LIST_DIR}/CSVOutputFormatStrategy.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CSVOutputFormatStrategy.h
        ${CMAKE_CURRENT_LIST_DIR}/STDOutputFormatStrategy.cpp
        ${CMAKE_CURRENT_LIST_DIR}/STDOutputFormatStrategy.h
        ${CMAKE_CURRENT_LIST_DIR}/CmdLineArguments.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CmdLineArguments.h
        ${CMAKE_CURRENT_LIST_DIR}/FormatStrategyFactory.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FormatStrategyFactory.h
        ${CMAKE_CURRENT_LIST_DIR}/InputManager.cpp
        ${CMAKE_CURRENT_LIST_DIR}/InputManager.h
        ${CMAKE_CURRENT_LIST_DIR}/Logger.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Logger.h
)
add_library(toobad4ml::io ALIAS toobad4ml_io)

target_include_directories(toobad4ml_io
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>
)

target_link_libraries(toobad4ml_io
    PRIVATE
        ClangLibTooling
)