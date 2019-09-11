#   CMakeLists.txt - CMake file for the "io" module. This file
#                    provides the following target:
#
#                           * io
#

cmake_minimum_required(VERSION 3.1)

project(io)


# Target
# -----------------------------------------------------------------------------

add_library(${PROJECT_NAME}
    STATIC
        FileManager.cpp
        FunctionTypeTranslator.cpp
        CSVOutputFormatStrategy.cpp
        STDOutputFormatStrategy.cpp
        CmdLineArguments.cpp
        FormatStrategyFactory.cpp
	    InputManager.cpp
        Logger.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        LibTooling
)
