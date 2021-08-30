#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CodePropertyGraph.h"
#include "description/LengthType.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "description/MockDescriptor.h"
#include "description/BufferOverflow.h"
#include "description/BufferOverflowBuilder.h"

namespace TOOBAD4ML{

namespace description{

class LengthTypeTest: 
    public ::testing::Test {

protected:
    void SetUp() override {
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());
        cBufferOverflowBuilder BOFBuilder;

        std::vector<std::string> Sources;
        Sources.push_back("data/lengthtype.c");

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
            cCodePropertyGraph *cpg = new cCodePropertyGraph(*(vuln.first));
            cpgs.push_back(cpg);
            for (auto const& vulnLOCIter : vuln.second) {
                cBufferOverflow bof = BOFBuilder.CreateBufferOverflow(*vulnLOCIter, *cpg);
                bofs.push_back(bof);
            }
        }

        lengthType = new cLengthType(new cMockDescriptor);
    
    }

    void TearDown() override {
        cpgs.clear();
        bofs.clear();
        delete lengthType;
    }

    // ATTRIBUTES
    std::vector<cCodePropertyGraph*> cpgs;
    std::vector<cBufferOverflow> bofs;
    cLengthType* lengthType;
};

TEST_F(LengthTypeTest, IntIndex) {
    ASSERT_EQ(lengthType->ExtractFeature(*cpgs[0], bofs[0]), "0;");

}

TEST_F(LengthTypeTest, Addition) {
    ASSERT_EQ(lengthType->ExtractFeature(*cpgs[0], bofs[1]), "1;");

}
TEST_F(LengthTypeTest, Subtraction) {
    ASSERT_EQ(lengthType->ExtractFeature(*cpgs[0], bofs[2]), "1;");

}
TEST_F(LengthTypeTest, Multiplication) {
    ASSERT_EQ(lengthType->ExtractFeature(*cpgs[0], bofs[3]), "2;");

}
TEST_F(LengthTypeTest, Division) {
    ASSERT_EQ(lengthType->ExtractFeature(*cpgs[0], bofs[4]), "2;");

}
TEST_F(LengthTypeTest, Modulus) {
    ASSERT_EQ(lengthType->ExtractFeature(*cpgs[0], bofs[5]), "3;");

}
TEST_F(LengthTypeTest, Function) {
    ASSERT_EQ(lengthType->ExtractFeature(*cpgs[0], bofs[6]), "4;");

}
TEST_F(LengthTypeTest, Pow) {
    ASSERT_EQ(lengthType->ExtractFeature(*cpgs[0], bofs[7]), "3;");

}
TEST_F(LengthTypeTest, Sqrt) {
    ASSERT_EQ(lengthType->ExtractFeature(*cpgs[0], bofs[8]), "3;");

}
TEST_F(LengthTypeTest, ArrayAccess) {
    ASSERT_EQ(lengthType->ExtractFeature(*cpgs[0], bofs[9]), "5;");

}
TEST_F(LengthTypeTest, RightShift) {
    ASSERT_EQ(lengthType->ExtractFeature(*cpgs[0], bofs[10]), "2;");

}
TEST_F(LengthTypeTest, LeftShift) {
    ASSERT_EQ(lengthType->ExtractFeature(*cpgs[0], bofs[11]), "2;");

}
TEST_F(LengthTypeTest, MultiplicationAndAddition) {
    ASSERT_EQ(lengthType->ExtractFeature(*cpgs[0], bofs[12]), "2;");

}


}

}
