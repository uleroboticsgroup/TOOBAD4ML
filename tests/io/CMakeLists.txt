cmake_minimum_required(VERSION 3.1)

project(io_test)


# Target
# -----------------------------------------------------------------------------

add_executable(${PROJECT_NAME}
    CSVOutputFormatStrategyTest.cpp
    STDOutputFormatStrategyTest.cpp
    FormatStrategyFactoryTest.cpp
    FileManagerTest.cpp
    InputManagerTest.cpp
    CmdLineArgumentsTest.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
	    io
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
