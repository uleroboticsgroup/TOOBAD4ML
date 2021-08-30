#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CodePropertyGraph.h"
#include "description/IndexType.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "description/MockDescriptor.h"
#include "description/BufferOverflow.h"
#include "description/BufferOverflowBuilder.h"

namespace TOOBAD4ML{

namespace description{

class IndexTypeTest: 
    public ::testing::Test {

protected:
    void SetUp() override {
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());
        cBufferOverflowBuilder BOFBuilder;

        std::vector<std::string> Sources;
        Sources.push_back("data/indextype.c");

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

        indexType = new cIndexType(new cMockDescriptor);
    
    }

    void TearDown() override {
        cpgs.clear();
        bofs.clear();
        delete indexType;
    }

    // ATTRIBUTES
    std::vector<cCodePropertyGraph*> cpgs;
    std::vector<cBufferOverflow> bofs;
    cIndexType* indexType;
};

TEST_F(IndexTypeTest, RegularAccess) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[0]), "0;");
}

TEST_F(IndexTypeTest, Addition) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[1]), "1;");

}
TEST_F(IndexTypeTest, Subtraction) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[2]), "1;");

}
TEST_F(IndexTypeTest, Multiplication) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[3]), "2;");

}
TEST_F(IndexTypeTest, Division) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[4]), "2;");

}
TEST_F(IndexTypeTest, Modulus) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[5]), "3;");

}
TEST_F(IndexTypeTest, Function) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[6]), "4;");
}

TEST_F(IndexTypeTest, FunctionAddress) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[7]), "4;");
}

TEST_F(IndexTypeTest, ArrayAccess) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[8]), "5;");

}

TEST_F(IndexTypeTest, ArrayAccessAddressAddition) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[9]), "5;");
}

TEST_F(IndexTypeTest, ArrayAccessAddress) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[10]), "5;");
}

TEST_F(IndexTypeTest, AddressAddition) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[11]), "1;");
}

TEST_F(IndexTypeTest, AddressSubtraction) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[12]), "1;");
}

TEST_F(IndexTypeTest, RightShift) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[13]), "2;");
}
TEST_F(IndexTypeTest, LeftShift) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[14]), "2;");
}

TEST_F(IndexTypeTest, MultiplicationAndAddition) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[15]), "2;");
}


TEST_F(IndexTypeTest, Pow) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[16]), "3;");

}
TEST_F(IndexTypeTest, Sqrt) {
    ASSERT_EQ(indexType->ExtractFeature(*cpgs[0], bofs[17]), "3;");

}

}

}
