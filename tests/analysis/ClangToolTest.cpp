// ----------------------------------------------------------------------------
#include "analysis/ClangTool.h"
// ----------------------------------------------------------------------------
#include <gtest/gtest.h>
// ----------------------------------------------------------------------------

// TODO Create a directory with tests files.


namespace TOOBAD4ML {

namespace analysis {

// FIXTURE CLASS
// ----------------------------------------------------------------------------

class ClangToolTest
    : public ::testing::Test {

protected:

    ClangToolTest()
    : fileSource({PROGRAM_NAME, "test.c"}),
      dirSource({PROGRAM_NAME, "."}),
      mixedSource({PROGRAM_NAME, "test.c", "."}) {}

    // ATTRIBUTES
    // ------------------------------------------------------------------------
    const std::string PROGRAM_NAME = "TOOBAD4ML";
    std::vector<char*> fileSource;
    std::vector<char*> dirSource;
    std::vector<char*> mixedSources;

};

// CONSTRUCTORS TESTS
// ----------------------------------------------------------------------------

TEST_F(ClangToolTest, CreateFromCmdLineWithFileSource) {
    // TODO
}

TEST_F(ClangToolTest, CreateWithFileSource) {
    // TODO
}

TEST_F(ClangToolTest, CreateFromCmdLineWithDirSource) {
    // TODO
}

TEST_F(ClangToolTest, CreateWithDirSource) {
    // TODO
}

TEST_F(ClangToolTest, CreateFromCmdLineWithMultipleMixedSources) {
    // TODO
}

TEST_F(ClangToolTest, CreateWithMultipleMixedSources) {
    //TODO
}


// METHODS TESTS
// ----------------------------------------------------------------------------

TEST_F(ClangToolTest, RunValidAction) {
    // TODO
}

TEST_F(ClangToolTest, RunInvalidAction) {
    // TODO
}

} /* analysis */

} /* TOOBAD4ML */
