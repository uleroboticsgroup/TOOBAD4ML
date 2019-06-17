#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "analysis/ModelBOFConsumer.h"
#include "ASTTraversal/FindSelectedASTNodesVisitor.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"

// ----------------------------------------------------------------------------

namespace TOOBAD4ML {

namespace ASTTraversal {

class FindSelectedASTNodesVisitorTest: public ::testing::Test {
protected:

    void SetUp() override {
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());

        std::vector<std::string> Sources;
        Sources.push_back("../../../data/test.c");
        Sources.push_back("../../../data/testEmpty.c");
        Sources.push_back("../../../data/testSeveral.c");

        clang::tooling::ClangTool Tool(Compilations, Sources);

        std::vector<std::unique_ptr<clang::ASTUnit>> ASTs;
        Tool.buildASTs(ASTs);

        AST = std::move(ASTs[0]);
        ASTEmpty = std::move(ASTs[1]);
        ASTSeveral = std::move(ASTs[2]);

        // 1 line
        clang::FileID mainFID = AST.get()->getASTContext().getSourceManager().getMainFileID();

        BOFLocation parsedLine(
            AST.get()->getASTContext().getSourceManager().translateLineCol(mainFID, 5, 1),
            AST.get()->getASTContext().getSourceManager().translateLineCol(mainFID, 5, 18));

        vulnerableLines.push_back(parsedLine);

        // 2 lines
        clang::FileID mainFIDSeveral = ASTSeveral.get()->getASTContext().getSourceManager().getMainFileID();

        BOFLocation parsedLine1(
            ASTSeveral.get()->getASTContext().getSourceManager().translateLineCol(mainFIDSeveral, 5, 1),
            ASTSeveral.get()->getASTContext().getSourceManager().translateLineCol(mainFIDSeveral, 5, 18));

        BOFLocation parsedLine2(
            ASTSeveral.get()->getASTContext().getSourceManager().translateLineCol(mainFIDSeveral, 6, 1),
            ASTSeveral.get()->getASTContext().getSourceManager().translateLineCol(mainFIDSeveral, 6, 18));
            
        vulnerableLinesSeveral.push_back(parsedLine1);
        vulnerableLinesSeveral.push_back(parsedLine2);
    }


    // ATTRIBUTES
    std::unique_ptr<clang::ASTUnit> AST;
    std::unique_ptr<clang::ASTUnit> ASTEmpty;
    std::unique_ptr<clang::ASTUnit> ASTSeveral;

    // TYPE DEFINITION:
    // Class: cExtractVulnerabilitiesVisitor
    // typedef std::pair<clang::SourceLocation, clang::SourceLocation> BOFLocation;
    std::vector<BOFLocation> vulnerableLines;
    std::vector<BOFLocation> vulnerableLinesEmpty;
    std::vector<BOFLocation> vulnerableLinesSeveral;


};

TEST_F(FindSelectedASTNodesVisitorTest, isVulnerable) {
    cFindSelectedASTNodesVisitor finder(vulnerableLines);

    finder.TraverseDecl(AST.get()->getASTContext().getTranslationUnitDecl());
    std::vector<clang::Expr*> selectedNodes = finder.GetSelectedNodes();
    ASSERT_EQ(selectedNodes.size(), 1);
    std::string output(selectedNodes[0]->getStmtClassName(),
    selectedNodes[0]->getStmtClassName() + 8);
    ASSERT_EQ(output, "CallExpr");
}

TEST_F(FindSelectedASTNodesVisitorTest, isVulnerableEmpty) {
    cFindSelectedASTNodesVisitor finder(vulnerableLinesEmpty);

    finder.TraverseDecl(ASTEmpty.get()->getASTContext().getTranslationUnitDecl());
    std::vector<clang::Expr*> selectedNodes = finder.GetSelectedNodes();
    ASSERT_EQ(selectedNodes.size(), 0);
}

TEST_F(FindSelectedASTNodesVisitorTest, isVulnerableSeveral) {
    cFindSelectedASTNodesVisitor finder(vulnerableLinesSeveral);

    finder.TraverseDecl(ASTSeveral.get()->getASTContext().getTranslationUnitDecl());
    std::vector<clang::Expr*> selectedNodes = finder.GetSelectedNodes();
    ASSERT_EQ(selectedNodes.size(), 2);
    
    std::string output(selectedNodes[0]->getStmtClassName(),
    selectedNodes[0]->getStmtClassName() + 8);
    ASSERT_EQ(output, "CallExpr");

    std::string output2(selectedNodes[1]->getStmtClassName(),
    selectedNodes[1]->getStmtClassName() + 8);
    ASSERT_EQ(output2, "CallExpr");
}

TEST_F(FindSelectedASTNodesVisitorTest, Constructor) {
    std::unique_ptr<cFindSelectedASTNodesVisitor> finder(new cFindSelectedASTNodesVisitor(vulnerableLines));

    ASSERT_TRUE(finder != nullptr);
}


} /* TOOBAD4ML */

} /* analysis */