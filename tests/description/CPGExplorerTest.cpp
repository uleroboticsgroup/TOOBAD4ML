#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CPGExplorer.h"
#include "description/CodePropertyGraph.h"
#include "description/PadmanabhuniBuilder.h"
#include "description/SinkClassification.h"
#include "description/MockDescriptor.h"
#include "description/BufferOverflow.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
//#include "route.h"

namespace TOOBAD4ML{

namespace description{

class CPGExplorerTest: 
    public ::testing::Test {

protected:
    void SetUp() override {
        builder = new cPadmanabhuniBuilder();
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());

        std::vector<std::string> Sources;
        //Sources.push_back(std::string(my_argv[1]) + "/sinkTypes.c");
        Sources.push_back("data/sinkTypes.c");

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
    cPadmanabhuniBuilder* builder;
};

TEST_F(CPGExplorerTest, Inspect) {
    cCPGExplorer* explorer = new cCPGExplorer(*builder->CreateDescriptor());
    std::string result = explorer->Inspect(*cpgs[0], *bofs[0]);
    EXPECT_EQ(result, "1;0;0;0;0;-1;-1;-1;1;-1;");
}

TEST_F(CPGExplorerTest, Constructor) {
    cCPGExplorer* explorer = new cCPGExplorer(*builder->CreateDescriptor());
    EXPECT_TRUE(explorer != nullptr);
}



TEST_F(CPGExplorerTest, SetDescriptor) {
    cCPGExplorer* explorer = new cCPGExplorer(*builder->CreateDescriptor());
    cMockDescriptor* mock = new cMockDescriptor();
    explorer->SetDescriptor(*mock);
    std::string result = explorer->Inspect(*cpgs[0], *bofs[0]);
    EXPECT_EQ(result, "");
}

}

}
