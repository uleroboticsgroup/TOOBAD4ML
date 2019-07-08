// ----------------------------------------------------------------------------
#include <gtest/gtest.h>
#include "analysis/ClangTool.h"
#include "io/InputManager.h"
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// TODO Create a directory with tests files.



namespace TOOBAD4ML {

namespace analysis {

// FIXTURE CLASS
// ----------------------------------------------------------------------------

class ClangToolTest
    : public ::testing::Test {

protected:

    ClangToolTest() {}

    // ATTRIBUTES
    // ------------------------------------------------------------------------
    const char* PROGRAM_NAME = "TOOBAD4ML";
};

// As this suite includes death tests, create an alias for the fixture
// src: https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#death-test-naming
//using ClangToolDeathTest = ClangToolTest;

/*
// ISSUE: Cannot test no arguments
TEST_F(ClangToolTest, CreateFromCmdLineWithoutFileSource) {
    const char* empty[1] = {PROGRAM_NAME};
    cClangTool clangTool(1, empty);
    cClangToolTest cClangToolTest;
    ASSERT_FALSE(cClangToolTest.checkIfClangToolExists(clangTool));
}
*/

TEST_F(ClangToolTest, CreateFromCmdLineWithMultipleFileSource) {
    IO::cInputManager* im = new IO::cInputManager();
    const char* multipleFiles[3] = {PROGRAM_NAME, "data/testEmpty.c", "data/testSeveral.c"};

    cClangTool* clangTool = new cClangTool(im->GetSourceFromCommandLine(3, multipleFiles));
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(*clangTool));
    delete clangTool;
}

TEST_F(ClangToolTest, CreateFromCmdLineWithMultipleMixedSources) {
    IO::cInputManager* im = new IO::cInputManager();
    const char* mixedSources[3] = {PROGRAM_NAME, "data/test.c", "data/*.c"};

    cClangTool* clangTool = new cClangTool(im->GetSourceFromCommandLine(3, mixedSources));
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(*clangTool));
    delete clangTool;
}

TEST_F(ClangToolTest, CreateFromCmdLineWithDirSource) {
    IO::cInputManager* im = new IO::cInputManager();
    const char* dirSource[2] = {PROGRAM_NAME, "data/*.c"};

    cClangTool* clangTool = new cClangTool(im->GetSourceFromCommandLine(2, dirSource));
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(*clangTool));
    delete clangTool;
}

/*
TEST_F(ClangToolTest, CreateWithSingleFileSource) {
    const char* fileSource[2] = {PROGRAM_NAME, "data/test.c"};

    cClangTool* clangTool = new cClangTool(IO::InputManager::GetSourceFromCommandLine(2, fileSource));
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(*clangTool));
    delete clangTool;
}

TEST_F(ClangToolTest, CreateFromCmdLineWithSingleFileSource) {
    const char* fileSource[2] = {PROGRAM_NAME, "data/test.c"};

    cClangTool* clangTool = new cClangTool(2, fileSource);
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(*clangTool));
    delete clangTool;
}
TEST_F(ClangToolTest, CreateWithMultipleFileSource) {
    const char* multipleFiles[3] = {PROGRAM_NAME, "data/testEmpty.c", "data/testSeveral.c"};

    cClangTool* clangTool = new cClangTool(IO::InputManager::GetSourceFromCommandLine(3, multipleFiles));
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(*clangTool));
    delete clangTool;
}

TEST_F(ClangToolTest, CreateWithMultipleMixedSources) {
    const char* mixedSources[3] = {PROGRAM_NAME, "data/test.c", "data/*.c"};

    cClangTool* clangTool = new cClangTool(IO::InputManager::GetSourceFromCommandLine(3, mixedSources));
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(*clangTool));
    delete clangTool;
}

TEST_F(ClangToolTest, CreateWithDirSource) {
    const char* dirSource[2] = {PROGRAM_NAME, "data/*.c"};

    cClangTool* clangTool = new cClangTool(IO::InputManager::GetSourceFromCommandLine(2, dirSource));
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(*clangTool));
    delete clangTool;
}
*/

} /* analysis */

} /* TOOBAD4ML */
