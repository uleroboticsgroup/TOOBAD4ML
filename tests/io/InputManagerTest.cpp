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
      mixedSources({PROGRAM_NAME, "test.c", "."}) {
          inputManager = new cInputManager();
      }

    // ATTRIBUTES
    // ------------------------------------------------------------------------
    const char* PROGRAM_NAME = "TOOBAD4ML";
    const char* fileSource[2];
    const char* multipleFiles[4];
    const char* dirSource[2];
    const char* mixedSources[3];
    cInputManager* inputManager;

};

// ------------------------------------------------------------------------------------
// GetSourceFromCommandLine
// ------------------------------------------------------------------------------------

TEST_F(InputManagerTest, GetSourceFromCommandLineSingleFile) {
    int i = 1;
    for (std::string file: inputManager->GetSourceFromCommandLine(2, fileSource).getSources()) {
        ASSERT_EQ(file, fileSource[i++]);
    }
}

TEST_F(InputManagerTest, GetSourceFromCommandLineMultipleFiles) {
    int i = 1;
    for (std::string file: inputManager->GetSourceFromCommandLine(4, multipleFiles).getSources()) {
        ASSERT_EQ(file, multipleFiles[i++]);
    }
}

TEST_F(InputManagerTest, GetSourceFromCommandLineMixedSources) {
    int i = 1;
    for (std::string file: inputManager->GetSourceFromCommandLine(3, mixedSources).getSources()) {
        ASSERT_EQ(file, mixedSources[i++]);
    }
}


TEST_F(InputManagerTest, GetSourceFromCommandLineDirectory) {
    int i = 1;
    for (std::string file: inputManager->GetSourceFromCommandLine(2, dirSource).getSources()) {
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
    ASSERT_NE(inputManager->GetCompilationDatabase("").get(), nullptr);
}

} /* TOOBAD4ML */

} /* IO */