#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CodePropertyGraph.h"
#include "description/StringCopyWithinBounds.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "description/MockDescriptor.h"
#include "description/BufferOverflow.h"


namespace TOOBAD4ML{

namespace description{

class cStringCopyWithinBoundsTest: 
    public ::testing::Test {

protected:

    cStringCopyWithinBoundsTest():
        scw(new cMockDescriptor) {}

    void SetUp() override {
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());

        std::vector<std::string> Sources;
        Sources.push_back("../../../data/strcpy.c");

        clang::tooling::ClangTool Tool(Compilations, Sources);

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
    cStringCopyWithinBounds scw;
};

//Type 1
TEST_F(cStringCopyWithinBoundsTest, WithinBounds) {
    ASSERT_EQ(scw.ExtractFeature(*cpgs[0], *bofs[0]), "1;");

}

//Type 0
TEST_F(cStringCopyWithinBoundsTest, OutsideBounds) {
    ASSERT_EQ(scw.ExtractFeature(*cpgs[1], *bofs[1]), "0;");
}


//Type -1
TEST_F(cStringCopyWithinBoundsTest, NotAplicable) {
    ASSERT_EQ(scw.ExtractFeature(*cpgs[2], *bofs[2]), "-1;");

}

}

}
