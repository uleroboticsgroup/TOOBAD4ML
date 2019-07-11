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
    : fileSources({PROGRAM_NAME, "data/test.c", "data/testEmpty.c", "data/test_load_folder/*.c"}){
        inputManager = new cInputManager();
    }

    // ATTRIBUTES
    // ------------------------------------------------------------------------
    const char* PROGRAM_NAME = "TOOBAD4ML";
    const char* fileSources[4];
    cInputManager* inputManager;
};

// ------------------------------------------------------------------------------------
// GetSourceFromCommandLine
// ------------------------------------------------------------------------------------

TEST_F(InputManagerTest, GetSourceFromCommandLineFile) {
    int i = 1;
    std::vector<std::string> sources = inputManager->GetSourceFromCommandLine(4, fileSources).getSources();

    EXPECT_EQ(3, sources.size());

    for(int i = 0; i < sources.size(); i++) {
        EXPECT_EQ(fileSources[i+1], sources[i]);
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