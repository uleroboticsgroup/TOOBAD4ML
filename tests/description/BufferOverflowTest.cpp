#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CodePropertyGraph.h"
#include "description/PadmanabhuniBuilder.h"
#include "description/BufferOverflow.h"
#include "description/BufferOverflowBuilder.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
//#include "route.h"

namespace TOOBAD4ML{

namespace description{

class BufferOverflowTest: 
    public ::testing::Test {

protected:
    void SetUp() override {
        builder = new cPadmanabhuniBuilder();
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());
        cBufferOverflowBuilder BOFBuilder;

        std::vector<std::string> Sources;
        //Sources.push_back(std::string(my_argv[1]) + "/sinkTypes.c");
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
            cCodePropertyGraph* cpg = new cCodePropertyGraph(*(vuln.first));
    
            for (auto const& vulnLOCIter : vuln.second) {
                bof = std::unique_ptr<cBufferOverflow>(& BOFBuilder.CreateBufferOverflow(*vulnLOCIter, *cpg));
                sink = vulnLOCIter;
            }
        }
    }

    void TearDown() override {
        delete builder;

    }
    // ATTRIBUTES
    clang::Expr* sink;
    std::unique_ptr<cBufferOverflow> bof;
    cPadmanabhuniBuilder* builder;
};

TEST_F(BufferOverflowTest, Constructor) {
    EXPECT_TRUE(bof.get() != nullptr);
}

TEST_F(BufferOverflowTest, GetInput) {
    std::vector<clang::CallExpr*> bof_input = bof.get()->GetInput();
    
    EXPECT_EQ(1, bof_input.size());
    EXPECT_EQ("gets", bof_input[0]->getDirectCallee()->getNameAsString());
}

TEST_F(BufferOverflowTest, GetBuffer) {
    clang::DeclRefExpr* bof_buffer = bof.get()->GetBuffer(BufferType::DST);
    
    EXPECT_EQ("buffer", bof_buffer->getNameInfo().getAsString());
}

TEST_F(BufferOverflowTest, GetSink) {
    clang::Expr* bof_sink = bof.get()->GetSink();
    EXPECT_EQ(sink, bof_sink);
}

}

}
