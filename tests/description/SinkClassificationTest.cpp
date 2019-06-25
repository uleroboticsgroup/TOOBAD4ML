#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CodePropertyGraph.h"
#include "description/SinkClassification.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "description/MockDescriptor.h"
#include "description/BufferOverflow.h"


namespace TOOBAD4ML{

namespace description{

class SinkClassificationTest: 
    public ::testing::Test {

protected:

    SinkClassificationTest():
        sc(new cMockDescriptor) {}

    void SetUp() override {
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());

        std::vector<std::string> Sources;
        Sources.push_back("../../../data/sinkTypes.c");

        clang::tooling::ClangTool Tool(Compilations, Sources);

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
                cBufferOverflow* bof = new cBufferOverflow(*vulnLOCIter);
			    bof->SetInput(*cpg);
                bofs.push_back(bof);
            }
            cpgs.push_back(cpg);
        }
    }


    // ATTRIBUTES
    std::vector<cCodePropertyGraph*> cpgs;
    std::vector<cBufferOverflow*> bofs;
    cSinkClassification sc;

};

TEST_F(SinkClassificationTest, Constructor) {
    ASSERT_TRUE(&sc != nullptr);
}

// Type 1
TEST_F(SinkClassificationTest, ExtractFeatureStrcpy) {
    ASSERT_EQ(sc.ExtractFeature(*cpgs[0], *bofs[0]), "1;");
}

TEST_F(SinkClassificationTest, ExtractFeatureStrncpy) {
    ASSERT_EQ(sc.ExtractFeature(*cpgs[1], *bofs[1]), "1;");
}

// Type 2
TEST_F(SinkClassificationTest, ExtractFeatureStrcat) {
    ASSERT_EQ(sc.ExtractFeature(*cpgs[2], *bofs[2]), "2;");
}

TEST_F(SinkClassificationTest, ExtractFeatureStrncat) {
    ASSERT_EQ(sc.ExtractFeature(*cpgs[3], *bofs[3]), "2;");
}

// Type 3
TEST_F(SinkClassificationTest, ExtractFeatureMemcpy) {
    ASSERT_EQ(sc.ExtractFeature(*cpgs[4], *bofs[4]), "3;");
}

// Type 4
TEST_F(SinkClassificationTest, ExtractFeatureMemmove) {
    ASSERT_EQ(sc.ExtractFeature(*cpgs[5], *bofs[5]), "4;");
}

TEST_F(SinkClassificationTest, ExtractFeatureSprintf) {
    ASSERT_EQ(sc.ExtractFeature(*cpgs[6], *bofs[6]), "4;");
}

// Type 5
TEST_F(SinkClassificationTest, ExtractFeatureSnprintf) {
    ASSERT_EQ(sc.ExtractFeature(*cpgs[7], *bofs[7]), "5;");
}

TEST_F(SinkClassificationTest, ExtractFeatureGets) {
    ASSERT_EQ(sc.ExtractFeature(*cpgs[8], *bofs[8]), "5;");
}

// Type 6
TEST_F(SinkClassificationTest, ExtractFeatureFgets) {
    ASSERT_EQ(sc.ExtractFeature(*cpgs[9], *bofs[9]), "6;");
}

TEST_F(SinkClassificationTest, ExtractFeatureScanf) {
    ASSERT_EQ(sc.ExtractFeature(*cpgs[10], *bofs[10]), "6;");
}

// Type 7
TEST_F(SinkClassificationTest, ExtractFeatureSscanf) {
    ASSERT_EQ(sc.ExtractFeature(*cpgs[11], *bofs[11]), "7;");
}



}

}
