// ----------------------------------------------------------------------------
#include <gtest/gtest.h>
#include "analysis/ClangTool.h"
#include "io/InputManager.h"
#include "io/CmdLineArguments.h"
#include "analysis/ModelBOFAction.h"
#include "analysis/ModelBOFFrontendActionFactory.h"
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
    // ----------------------------------------------------------------------
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

TEST_F(ClangToolTest, CreateFromCmdLineWithFileSource) {
    std::vector<std::string> files;
    
    files.push_back("data/testEmpty.c");
    std::map<IO::eFlagsType, std::string> flags;

    IO::sCmdLineArguments cmdArgs(files, flags);
    cClangTool* clangTool = new cClangTool(cmdArgs);
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(*clangTool));
}

TEST_F(ClangToolTest, CreateFromCmdLineWithMultipleSources) {
    std::vector<std::string> files;
    
    files.push_back("data/testEmpty.c");
    files.push_back("data/testSeveral.c");
    std::map<IO::eFlagsType, std::string> flags;

    IO::sCmdLineArguments cmdArgs(files, flags);
    cClangTool* clangTool = new cClangTool(cmdArgs);
    cClangToolTest cClangToolTest;
    ASSERT_TRUE(cClangToolTest.checkIfClangToolExists(*clangTool));
}

TEST_F(ClangToolTest, Run) {
    std::vector<std::string> files;
    
    files.push_back("data/test.c");
    std::map<IO::eFlagsType, std::string> flags;

    flags.insert(std::make_pair(IO::eFlagsType::OUTPUT_EXTENSION, "STD"));
    flags.insert(std::make_pair(IO::eFlagsType::OUTPUT_FILENAME, ""));

    IO::sCmdLineArguments cmdArgs(files, flags);
    cClangTool* clangTool = new cClangTool(cmdArgs);
    cModelBOFAction* action = new cModelBOFAction();
    cModelBOFFrontendActionFactory* factory = new cModelBOFFrontendActionFactory(*action);

    std::stringstream buffer;
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());
    EXPECT_EQ(0, clangTool->Run(factory));
    std::cout.rdbuf(coutbuf);
    
    std::size_t pos = buffer.str().find("Completed");      

    EXPECT_EQ(buffer.str().substr(pos), "Completed\nResults:\n5;1;0;0;0;-1;-1;-1;-1;-1;0;\n");
}

} /* analysis */

} /* TOOBAD4ML */