// ----------------------------------------------------------------------------
#include "analysis/ClangTool.h"
#include "io/InputManager.h"
// ----------------------------------------------------------------------------
#include <gtest/gtest.h>
// ----------------------------------------------------------------------------
// TODO Create a directory with tests files.



namespace TOOBAD4ML {

namespace analysis {


// FIXTURE CLASS
// ----------------------------------------------------------------------------

TEST(ClangToolDeathTest, CreateWithValidCmdLineInput) {

    int argc = 3;
    const char* argv[3] = {"TOOBAD4ML", "test.c", "--"};

    EXPECT_EXIT(
            cClangTool(argc, argv),
            ::testing::ExitedWithCode(0),
            "Success"
    );

}

TEST(ClangToolDeathTest, CreateWithInvalidCmdLineInput) {

    int argc = 0;
    const char** argv = nullptr;

    ASSERT_EXIT(
            cClangTool(argc, argv),
            ::testing::KilledBySignal(SIGABRT),
            ".*"
    );

}

TEST(ClangToolDeathTest, CreateWithValidFixedInput) {}

TEST(ClangToolDeathTest, CreateWithInvalidFixedInput) {}


// FIXTURE TESTS
// ----------------------------------------------------------------------------

class ClangToolTest : public ::testing::Test {
protected:

    ClangToolTest()
    : fileSource({PROGRAM_NAME, "test.c"}),
      multipleFiles({PROGRAM_NAME, "test.c", "test1.c", "test2.c"}),
      mixedSources({PROGRAM_NAME, "test.c", "."}),
      dirSource({PROGRAM_NAME, "."}) {};

    // ATTRIBUTES
    // ------------------------------------------------------------------------
    const char* PROGRAM_NAME = "TOOBAD4ML";
    const char* fileSource[2];
    const char* multipleFiles[4];
    const char* dirSource[2];
    const char* mixedSources[3];
};

// As this suite includes death tests, create an alias for the fixture
// src: https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#death-test-naming
using ClangToolDeathTest = ClangToolTest;

/* 
TEST_F(ClangToolTest, CreateFromCmdLineWithoutFileSource) {
    // ISSUE: Cannot test no arguments
    const char* empty[1] = {PROGRAM_NAME};
    cClangTool clangTool(1, empty);
    cClangToolTest cClangToolTest;
    ASSERT_FALSE(cClangToolTest.checkIfClangToolExists(clangTool));
}

TEST_F(ClangToolTest, CreateFromCmdLineWithFileSource) {
    cClangTool clangTool(2, fileSource);
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(clangTool));
}

TEST_F(ClangToolTest, CreateWithFileSource) {
    cClangTool clangTool(IO::InputManager::GetSourceFromCommandLine(2, fileSource));
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(clangTool));
}

TEST_F(ClangToolTest, CreateFromCmdLineWithMultipleFileSource) {
    cClangTool clangTool(4, multipleFiles);
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(clangTool));
}

TEST_F(ClangToolTest, CreateWithMultipleFileSource) {
    cClangTool clangTool(IO::InputManager::GetSourceFromCommandLine(4, multipleFiles));
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(clangTool));
}

TEST_F(ClangToolTest, CreateFromCmdLineWithDirSource) {
    cClangTool clangTool(2, dirSource);
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(clangTool));
}

TEST_F(ClangToolTest, CreateWithDirSource) {
    cClangTool clangTool(IO::InputManager::GetSourceFromCommandLine(2, dirSource));
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(clangTool));
}

TEST_F(ClangToolTest, CreateFromCmdLineWithMultipleMixedSources) {
    cClangTool clangTool(3, mixedSources);
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(clangTool));
}

TEST_F(ClangToolTest, CreateWithMultipleMixedSources) {
    cClangTool clangTool(IO::InputManager::GetSourceFromCommandLine(3, mixedSources));
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(clangTool));
}

TEST_F(ClangToolTest, RunValidActionWithoutData) {

    clang::tooling::ToolAction* action =
            clang::tooling::newFrontendActionFactory<cModelBOFAction>().get();
    ASSERT_TRUE(action != nullptr);

    EXPECT_EQ(0, toolWithoutData.Run(action));

}


TEST_F(ClangToolTest, RunInvalidAction) {

    EXPECT_EQ(0, toolWithData.Run(nullptr));

}
*/

} /* analysis */

} /* TOOBAD4ML */
