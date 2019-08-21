#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CodePropertyGraph.h"
#include "description/SizeSourceBuffer.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "description/MockDescriptor.h"
#include "description/BufferOverflow.h"
#include "description/BufferOverflowBuilder.h"

namespace TOOBAD4ML{

namespace description{

class cSizeSourceBufferTest: 
    public ::testing::Test {

protected:
    void SetUp() override {
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());
        cBufferOverflowBuilder BOFBuilder;

        std::vector<std::string> Sources;
        Sources.push_back("data/sizeofsource.c");

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

        slsb = new cSizeSourceBuffer(new cMockDescriptor);
    
    }

    void TearDown() override {
        cpgs.clear();
        bofs.clear();
        delete slsb;
    }

    // ATTRIBUTES
    std::vector<cCodePropertyGraph*> cpgs;
    std::vector<cBufferOverflow> bofs;
    cSizeSourceBuffer* slsb;
};

TEST_F(cSizeSourceBufferTest, Normal) {
    ASSERT_EQ(slsb->ExtractFeature(*cpgs[0], bofs[0]), "2;");

}

TEST_F(cSizeSourceBufferTest, Inside) {
    ASSERT_EQ(slsb->ExtractFeature(*cpgs[0], bofs[1]), "3;");
}


TEST_F(cSizeSourceBufferTest, DstBuffer) {
    ASSERT_EQ(slsb->ExtractFeature(*cpgs[0], bofs[2]), "3;");

}

}

}
