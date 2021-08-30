#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CodePropertyGraph.h"
#include "description/SizeDestinationBufferMinusX.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "description/MockDescriptor.h"
#include "description/BufferOverflow.h"
#include "description/BufferOverflowBuilder.h"

namespace TOOBAD4ML{

namespace description{

class SizeDestinationBufferMinusXTest: 
    public ::testing::Test {

protected:
    void SetUp() override {
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());
        cBufferOverflowBuilder BOFBuilder;

        std::vector<std::string> Sources;
        Sources.push_back("data/sizeofdestinationminusx.c");

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

        sdb = new cSizeDestinationBufferMinusX(new cMockDescriptor);
    
    }

    void TearDown() override {
        cpgs.clear();
        bofs.clear();
        delete sdb;
    }

    // ATTRIBUTES
    std::vector<cCodePropertyGraph*> cpgs;
    std::vector<cBufferOverflow> bofs;
    cSizeDestinationBufferMinusX* sdb;
};

TEST_F(SizeDestinationBufferMinusXTest, SrcBufferCheck) {
    ASSERT_EQ(sdb->ExtractFeature(*cpgs[0], bofs[0]), "0;");

}

TEST_F(SizeDestinationBufferMinusXTest, DstBufferMinusOne) {
    ASSERT_EQ(sdb->ExtractFeature(*cpgs[0], bofs[1]), "0;");
}

TEST_F(SizeDestinationBufferMinusXTest, DstBufferMinusZero) {
    ASSERT_EQ(sdb->ExtractFeature(*cpgs[0], bofs[2]), "0;");

}

TEST_F(SizeDestinationBufferMinusXTest, Any) {
    ASSERT_EQ(sdb->ExtractFeature(*cpgs[0], bofs[3]), "1;");

}

}

}
