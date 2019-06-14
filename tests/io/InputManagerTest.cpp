#include "io/InputManager.h"
// ----------------------------------------------------------------------------
#include <gtest/gtest.h>
// ----------------------------------------------------------------------------

namespace TOOBAD4ML {

namespace IO {

class InputManagerTest:
    public ::testing::Test {

protected:
    InputManagerTest()
    : fileSource({PROGRAM_NAME, "test.c"}),
      multipleFiles({PROGRAM_NAME, "test.c", "test1.c", "test2.c"}),
      dirSource({PROGRAM_NAME, "."}),
      mixedSources({PROGRAM_NAME, "test.c", "."}) {}

    // ATTRIBUTES
    // ------------------------------------------------------------------------
    const char* PROGRAM_NAME = "TOOBAD4ML";
    const char* fileSource[2];
    const char* multipleFiles[4];
    const char* dirSource[2];
    const char* mixedSources[3];

};

// ------------------------------------------------------------------------------------
// GetSourceFromCommandLine
// ------------------------------------------------------------------------------------

TEST_F(InputManagerTest, GetSourceFromCommandLineSingleFile) {
    int i = 1;
    for (std::string file: InputManager::GetSourceFromCommandLine(2, fileSource)) {
        ASSERT_EQ(file, fileSource[i++]);
    }
}

TEST_F(InputManagerTest, GetSourceFromCommandLineMultipleFiles) {
    int i = 1;
    for (std::string file: InputManager::GetSourceFromCommandLine(4, multipleFiles)) {
        ASSERT_EQ(file, multipleFiles[i++]);
    }
}

TEST_F(InputManagerTest, GetSourceFromCommandLineMixedSources) {
    int i = 1;
    for (std::string file: InputManager::GetSourceFromCommandLine(3, mixedSources)) {
        ASSERT_EQ(file, mixedSources[i++]);
    }
}


TEST_F(InputManagerTest, GetSourceFromCommandLineDirectory) {
    int i = 1;
    for (std::string file: InputManager::GetSourceFromCommandLine(2, dirSource)) {
        ASSERT_EQ(file, dirSource[i++]);
    }
}

// ------------------------------------------------------------------------------------
// GetCompilationDatabase
// ------------------------------------------------------------------------------------

TEST_F(InputManagerTest, GetCompilationDatabaseFile) {
    // TODO
    // Generate a DB file for the tests.
}


TEST_F(InputManagerTest, GetCompilationDatabaseDirectory) {
    // TODO
    // Generate a DB file for the tests.
}

TEST_F(InputManagerTest, GetCompilationDatabaseEmpty) {
    ASSERT_NE(InputManager::GetCompilationDatabase("").get(), nullptr);
}

} /* TOOBAD4ML */

} /* IO */