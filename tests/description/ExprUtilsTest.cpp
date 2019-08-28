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
                bofs.push_back(BOFBuilder.CreateBufferOverflow(*vulnLOCIter, *cpg));
            }
            break;
        }
        exprUtils = cExprUtils::GetInstance();
    }

    void TearDown() override {
        bofs.clear();
        delete cpg;
    }

    // ATTRIBUTES
    std::vector<cBufferOverflow> bofs;
    cCodePropertyGraph *cpg;
    cExprUtils* exprUtils;
};

TEST_F(ExprUtilsTest, GetInstance) {
    EXPECT_NE(nullptr, exprUtils);
    EXPECT_EQ(exprUtils, cExprUtils::GetInstance());
}

TEST_F(ExprUtilsTest, GuessBufferSizeConstantArray) {
    EXPECT_EQ(256, exprUtils->guessBufferSize(bofs[0].GetBuffer(BufferType::DST), cpg->GetAST().getASTContext()));
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
    EXPECT_EQ(256, exprUtils->guessArgumentSize(bofs[0].GetBuffer(BufferType::DST), cpg->GetAST().getASTContext()));
}

TEST_F(ExprUtilsTest, GuessArgumentSizeIntegerLiteral) {
    clang::BinaryOperator* sink = llvm::dyn_cast<clang::BinaryOperator>(bofs[2].GetSink());
    EXPECT_EQ(2, exprUtils->guessArgumentSize(sink->getRHS(), cpg->GetAST().getASTContext()));
}
/*
TODO

TEST_F(ExprUtilsTest, GuessArgumentSizeUnaryExprOrTypeTraitExpr) {
}
*/

TEST_F(ExprUtilsTest, GetValueFromDeclRefExpr) {
    EXPECT_EQ("x", exprUtils->getValueFromDeclRefExpr(bofs[0].GetBuffer(BufferType::DST))->getNameAsString());
}


TEST_F(ExprUtilsTest, GetValueFromIntegerLiteral) {
    clang::BinaryOperator* sink = llvm::dyn_cast<clang::BinaryOperator>(bofs[2].GetSink());
    EXPECT_EQ(2, exprUtils->getValueFromIntegerLiteral(sink->getRHS()));
}

TEST_F(ExprUtilsTest, GetExprFromUnaryOperator) {
    clang::BinaryOperator* sink = llvm::dyn_cast<clang::BinaryOperator>(bofs[1].GetSink());
    clang::Expr* expr = exprUtils->getExprFromUnaryOperator(sink->getRHS());
    
    EXPECT_EQ("a", exprUtils->getValueFromDeclRefExpr(expr)->getNameAsString());
}

TEST_F(ExprUtilsTest, GetIndexFromArraySubscriptExpr) {
    clang::BinaryOperator* sink = llvm::dyn_cast<clang::BinaryOperator>(bofs[1].GetSink());
    clang::Expr* expr = exprUtils->getIndexFromArraySubscriptExpr(sink->getLHS());
    
    EXPECT_EQ(285, exprUtils->getValueFromIntegerLiteral(expr));
}

TEST_F(ExprUtilsTest, GetArrayFromArraySubscriptExpr) {
    clang::BinaryOperator* sink = llvm::dyn_cast<clang::BinaryOperator>(bofs[1].GetSink());
    clang::Expr* expr = exprUtils->getArrayFromArraySubscriptExpr(sink->getLHS());
    
    EXPECT_EQ("z", exprUtils->getValueFromDeclRefExpr(expr)->getNameAsString());}

TEST_F(ExprUtilsTest, GetFromComparisonBinaryOperator) {
    clang::BinaryOperator* sink = llvm::dyn_cast<clang::BinaryOperator>(bofs[3].GetSink());
    std::vector<clang::Expr*> found = exprUtils->getFromComparisonBinaryOperator(sink, clang::Stmt::StmtClass::ArraySubscriptExprClass);

    EXPECT_EQ(2, found.size());
    std::vector<std::string> expected = {"z", "x"};

    for(int i = 0; i < 2; i++) {
        clang::Expr* expr = exprUtils->getArrayFromArraySubscriptExpr(found[i]);
        EXPECT_EQ(expected[i], exprUtils->getValueFromDeclRefExpr(expr)->getNameAsString());
    }
}
