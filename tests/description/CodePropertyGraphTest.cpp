#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CodePropertyGraph.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"

namespace TOOBAD4ML{

namespace description{

class CodePropertyGraphTest: 
    public ::testing::Test {

protected:

    void SetUp() override {
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());

        std::vector<std::string> Sources;
        Sources.push_back("data/test.c");

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
            decl = vuln.first;
            break;
        }
    }


    // ATTRIBUTES
    clang::FunctionDecl* decl;
};

TEST_F(CodePropertyGraphTest, Constructor) {
    cCodePropertyGraph CPG(*decl);
    ASSERT_TRUE(&CPG.GetCFG() != nullptr);
}

}

}
