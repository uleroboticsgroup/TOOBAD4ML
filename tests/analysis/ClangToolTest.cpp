#include <gtest/gtest.h>

#include "analysis/ClangTool.h"
#include "analysis/ModelBOFAction.h"


namespace TOOBAD4ML {

namespace analysis {


// DEATH TESTS
// ----------------------------------------------------------------------------

TEST(ClangToolDeathTest, CreateWithValidCmdLineInput) {

    int argc = 3;
    const char* argv[argc] = {"TOOBAD4ML", "test.c", "--"};

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

    ClangToolTest() :
        toolWithData("test.c"),
        toolWithoutData("") {}

    cClangTool toolWithData;
    cClangTool toolWithoutData;

};

// As this suite includes death tests, create an alias for the fixture
// src: https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#death-test-naming
using ClangToolDeathTest = ClangToolTest;


TEST_F(ClangToolTest, RunValidAction) {

    clang::tooling::ToolAction* action =
            clang::tooling::newFrontendActionFactory<cModelBOFAction>().get();
    ASSERT_TRUE(action != nullptr);

    EXPECT_EQ(0, toolWithData.Run(action));

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

} /* analysis */

} /* TOOBAD4ML */
