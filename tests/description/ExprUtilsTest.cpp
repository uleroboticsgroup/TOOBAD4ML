#include "gtest/gtest.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CodePropertyGraph.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "description/BufferOverflow.h"
#include "description/BufferOverflowBuilder.h"
#include "description/ExprUtils.h"

using namespace TOOBAD4ML;
using namespace description;

class ExprUtilsTest
: public ::testing::Test {

protected:
    void SetUp() override {
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());
        cBufferOverflowBuilder BOFBuilder;

        std::vector<std::string> Sources;
        Sources.push_back("data/testGuessSizes.c");

        clang::tooling::ClangTool Tool(Compilations, Sources);
        Tool.setDiagnosticConsumer(new clang::IgnoringDiagConsumer());

        std::vector<std::unique_ptr<clang::ASTUnit>> ASTs;
        Tool.buildASTs(ASTs);

        std::unique_ptr<clang::ASTUnit> AST = std::move(ASTs[0]);

        ASTTraversal::cExtractVulnerabilitiesVisitor visitor(AST.get()->getASTContext());
        visitor.TraverseDecl(AST.get()->getASTContext().getTranslationUnitDecl());

        ASTTraversal::BOFNodesPerFunctionMap vulnerabilities =
            visitor.GetVulnerabilities();
        
        
        for (auto const& vuln: vulnerabilities) {
            cpg = new cCodePropertyGraph(*(vuln.first));
            
            for (auto const& vulnLOCIter : vuln.second) {
                bof = &(BOFBuilder.CreateBufferOverflow(*vulnLOCIter, *cpg));

                break;
            }
            break;
        }
        exprUtils = cExprUtils::GetInstance();
    }


    // ATTRIBUTES
    cBufferOverflow *bof;
    cCodePropertyGraph *cpg;
    cExprUtils* exprUtils;
};

TEST_F(ExprUtilsTest, GetInstance) {
    EXPECT_NE(nullptr, exprUtils);
    EXPECT_EQ(exprUtils, cExprUtils::GetInstance());
}

TEST_F(ExprUtilsTest, GuessBufferSizeConstantArray) {
    EXPECT_EQ(256, exprUtils->guessBufferSize(bof->GetBuffer(BufferType::DST), cpg->GetAST().getASTContext()));
}
/** 
 * TODO
 * 
 *  TEST_F(ExprUtilsTest, GuessBufferSizeIncompleteArray) {
    }
 *  TEST_F(ExprUtilsTest, GuessBufferSizeVariableArray) {
    }
    TEST_F(ExprUtilsTest, GuessBufferSizeDependentSizedArray) {
    }
    TEST_F(ExprUtilsTest, GuessBufferSizeDependentPointer) {
    }
 */


TEST_F(ExprUtilsTest, GuessArgumentSizeDeclRefExprClass) {
    EXPECT_EQ(256, exprUtils->guessArgumentSize(bof->GetBuffer(BufferType::DST), cpg->GetAST().getASTContext()));
}

/*

    TODO


    TEST_F(ExprUtilsTest, GuessArgumentSizeUnaryExprOrTypeTraitExpr) {
    }

    TEST_F(ExprUtilsTest, GuessArgumentSizeIntegerLiteral) {
    }
*/