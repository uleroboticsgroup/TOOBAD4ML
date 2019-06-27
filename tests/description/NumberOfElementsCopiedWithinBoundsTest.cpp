#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CodePropertyGraph.h"
#include "description/NumberOfElementsCopiedWithinBounds.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "description/MockDescriptor.h"
#include "description/BufferOverflow.h"


namespace TOOBAD4ML{

namespace description{

class NumberOfElementsCopiedWithinBoundsTest: 
    public ::testing::Test {

protected:

    NumberOfElementsCopiedWithinBoundsTest():
        noe(new cMockDescriptor) {}

    void SetUp() override {
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());

        std::vector<std::string> Sources;
        Sources.push_back("data/nelementscopied.c");

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
                cBufferOverflow *bof = new cBufferOverflow(*vulnLOCIter);
			    bof->SetInput(*cpg);
                bofs.push_back(bof);
            }
        }

    }


    // ATTRIBUTES
    std::vector<cCodePropertyGraph*> cpgs;
    std::vector<cBufferOverflow*> bofs;
    cNumberOfElementsCopiedWithinBounds noe;
};

//Type 0
TEST_F(NumberOfElementsCopiedWithinBoundsTest, GreaterThanDestination) {
    ASSERT_EQ(noe.ExtractFeature(*cpgs[0], *bofs[0]), "0;");

}

//Type 1
TEST_F(NumberOfElementsCopiedWithinBoundsTest, LessOrEqualThanDestination) {
    ASSERT_EQ(noe.ExtractFeature(*cpgs[1], *bofs[1]), "1;");
}


//Type -1
TEST_F(NumberOfElementsCopiedWithinBoundsTest, NotAplicable) {
    ASSERT_EQ(noe.ExtractFeature(*cpgs[2], *bofs[2]), "-1;");

}

//Type 2
TEST_F(NumberOfElementsCopiedWithinBoundsTest, NotEvaluable) {
    // UNABLE TO FIND REAL CASE
}

}

}
