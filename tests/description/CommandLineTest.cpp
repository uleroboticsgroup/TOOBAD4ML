#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CodePropertyGraph.h"
#include "description/CommandLine.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "description/MockDescriptor.h"
#include "description/BufferOverflow.h"


namespace TOOBAD4ML{

namespace description{

class CommandLineTest: 
    public ::testing::Test {

protected:

    void SetUp() override {
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());

        std::vector<std::string> Sources;
        Sources.push_back("data/test.c");
        Sources.push_back("data/inputTypes.c");

        clang::tooling::ClangTool Tool(Compilations, Sources);
        Tool.setDiagnosticConsumer(new clang::IgnoringDiagConsumer());

        std::vector<std::unique_ptr<clang::ASTUnit>> ASTs;
        Tool.buildASTs(ASTs);

        std::unique_ptr<clang::ASTUnit> AST = std::move(ASTs[0]);
        std::unique_ptr<clang::ASTUnit> ASTSeveral = std::move(ASTs[1]);

        ASTTraversal::cExtractVulnerabilitiesVisitor visitor(AST.get()->getASTContext());
        visitor.TraverseDecl(AST.get()->getASTContext().getTranslationUnitDecl());

        ASTTraversal::BOFNodesPerFunctionMap vulnerabilities =
            visitor.GetVulnerabilities();
        
        
        for (auto const& vuln: vulnerabilities) {
            cpg = new cCodePropertyGraph(*(vuln.first));
            
            for (auto const& vulnLOCIter : vuln.second) {
                bof = new cBufferOverflow(*vulnLOCIter);
			    bof->SetInput(*cpg);
                break;
            }
            break;
        }

        ASTTraversal::cExtractVulnerabilitiesVisitor visitorSeveral(ASTSeveral.get()->getASTContext());
        visitorSeveral.TraverseDecl(ASTSeveral.get()->getASTContext().getTranslationUnitDecl());

        ASTTraversal::BOFNodesPerFunctionMap severalVulnerabilities =
            visitorSeveral.GetVulnerabilities();
        
        
        for (auto const& vuln: severalVulnerabilities) {
            cpgSeveral = new cCodePropertyGraph(*(vuln.first));
            
            for (auto const& vulnLOCIter : vuln.second) {
                bofSeveral = new cBufferOverflow(*vulnLOCIter);
			    bofSeveral->SetInput(*cpgSeveral);
                break;
            }
            break;
        }
    }


    // ATTRIBUTES
    cCodePropertyGraph *cpg;
    cBufferOverflow *bof;

    cCodePropertyGraph *cpgSeveral;
    cBufferOverflow *bofSeveral;
};

TEST_F(CommandLineTest, Constructor) {
    cCommandLine cl(new cMockDescriptor);
    ASSERT_TRUE(&cl != nullptr);
}

TEST_F(CommandLineTest, ExtractFeature) {
    cCommandLine cl(new cMockDescriptor);
    ASSERT_EQ(cl.ExtractFeature(*cpg, *bof), "1;");
}

TEST_F(CommandLineTest, ExtractSeveralFeatures) {
    cCommandLine cl(new cMockDescriptor);
    ASSERT_EQ(cl.ExtractFeature(*cpgSeveral, *bofSeveral), "3;");
}

}

}
