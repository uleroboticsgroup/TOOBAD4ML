#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "description/CodePropertyGraph.h"
#include "description/AddressType.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "description/MockDescriptor.h"
#include "description/BufferOverflow.h"
#include "description/BufferOverflowBuilder.h"

namespace TOOBAD4ML{

namespace description{

class AddressTypeTest: 
    public ::testing::Test {

protected:
    void SetUp() override {
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());
        cBufferOverflowBuilder BOFBuilder;

        std::vector<std::string> Sources;
        Sources.push_back("data/addresstype.c");

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

        addressType = new cAddressType(new cMockDescriptor);
    
    }

    void TearDown() override {
        cpgs.clear();
        bofs.clear();
        delete addressType;
    }

    // ATTRIBUTES
    std::vector<cCodePropertyGraph*> cpgs;
    std::vector<cBufferOverflow> bofs;
    cAddressType* addressType;
};

TEST_F(AddressTypeTest, RegularAccess) {
    ASSERT_EQ(addressType->ExtractFeature(*cpgs[0], bofs[0]), "0;");

}

TEST_F(AddressTypeTest, Addition) {
    ASSERT_EQ(addressType->ExtractFeature(*cpgs[0], bofs[1]), "1;");

}
TEST_F(AddressTypeTest, Subtraction) {
    ASSERT_EQ(addressType->ExtractFeature(*cpgs[0], bofs[2]), "1;");

}
TEST_F(AddressTypeTest, Multiplication) {
    ASSERT_EQ(addressType->ExtractFeature(*cpgs[0], bofs[3]), "2;");

}
TEST_F(AddressTypeTest, Division) {
    ASSERT_EQ(addressType->ExtractFeature(*cpgs[0], bofs[4]), "2;");

}
TEST_F(AddressTypeTest, Modulus) {
    ASSERT_EQ(addressType->ExtractFeature(*cpgs[0], bofs[5]), "3;");

}
TEST_F(AddressTypeTest, FunctionAddition) {
    ASSERT_EQ(addressType->ExtractFeature(*cpgs[0], bofs[6]), "4;");

}

TEST_F(AddressTypeTest, Function) {
    ASSERT_EQ(addressType->ExtractFeature(*cpgs[0], bofs[7]), "4;");

}

TEST_F(AddressTypeTest, ArrayAccess) {
    ASSERT_EQ(addressType->ExtractFeature(*cpgs[0], bofs[8]), "5;");

}
TEST_F(AddressTypeTest, RightShift) {
    ASSERT_EQ(addressType->ExtractFeature(*cpgs[0], bofs[9]), "2;");

}
TEST_F(AddressTypeTest, LeftShift) {
    ASSERT_EQ(addressType->ExtractFeature(*cpgs[0], bofs[10]), "2;");

}

TEST_F(AddressTypeTest, Pow) {
    ASSERT_EQ(addressType->ExtractFeature(*cpgs[0], bofs[11]), "3;");

}
TEST_F(AddressTypeTest, Sqrt) {
    ASSERT_EQ(addressType->ExtractFeature(*cpgs[0], bofs[12]), "3;");

}

}

}
