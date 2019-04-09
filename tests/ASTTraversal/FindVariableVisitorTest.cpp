#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>

#include "ASTTraversal/FindVariableVisitorTest.h"
#include "analysis/StubModelBOFAction.h"

using namespace TOOBAD4ML;
using namespace ASTTraversal;


// TEST FIXTURES
// ----------------------------------------------------------------------------

cFindVariableVisitorTest::cFindVariableVisitorTest() {
    // Data to be used for the tests
    std::vector<std::string> testSources;

    // Create a stub tool
    clang::tooling::CommonOptionsParser OptionsParser(0, NULL, "Test");
    clang::tooling::ClangTool Tool(
            OptionsParser.getCompilations(), testSources);
    int result = Tool.run(
        clang::tooling::newFrontendActionFactory<analysis::cStubModelBOFAction>().get()
    );
}

void cFindVariableVisitorTest::SetUp(){
}

void cFindVariableVisitorTest::TearDown(){
}


// UNIT TESTS
// ----------------------------------------------------------------------------

// Tests default constructor
TEST_F(cFindVariableVisitorTest, DefaultConstructor) {
    EXPECT_FALSE(m_varFinderVisitor.IsFound());
}

// Tests whether a variable is present in the AST of a call expression.
TEST_F(cFindVariableVisitorTest, FindVariableInCallExpr) {
    // 1. Get the variable we want to find

    // 2. Traverse the visitor
    m_varFinderVisitor.TraverseDecl();

    // 3. Assert if found
    ASSERT_TRUE(m_varFinderVisitor.IsFound());
}
