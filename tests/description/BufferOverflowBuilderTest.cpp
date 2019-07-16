#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CodePropertyGraph.h"
#include "description/File.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "description/MockDescriptor.h"
#include "description/BufferOverflow.h"
#include "description/BufferOverflowBuilder.h"

namespace TOOBAD4ML{

namespace description{

class BufferOverflowBuilderTest: 
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
            cpg = new cCodePropertyGraph(*(vuln.first));
            for (auto const& vulnLOCIter : vuln.second) {
                sink = vulnLOCIter;
                break;
            }
            break;
        }
    }


    // ATTRIBUTES
    cCodePropertyGraph *cpg;
    clang::Expr* sink;
};

TEST_F(BufferOverflowBuilderTest, CreateBufferOverflow){
    cBufferOverflowBuilder BOFBuilder;
    cBufferOverflow bof = BOFBuilder.CreateBufferOverflow(*sink, *cpg);

    std::vector<clang::CallExpr*> bof_input = bof.GetInput();
    clang::DeclRefExpr* bof_buffer = bof.GetBuffer();
    clang::Expr* bof_sink = bof.GetSink();

    EXPECT_EQ(sink, bof_sink);

    EXPECT_EQ("buffer", bof_buffer->getNameInfo().getAsString());

    EXPECT_EQ(1, bof_input.size());
    EXPECT_EQ("gets", bof_input[0]->getDirectCallee()->getNameAsString());
}

}

}