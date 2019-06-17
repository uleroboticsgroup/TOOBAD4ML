#include <gtest/gtest.h>
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/Tooling.h"
#include "description/PadmanabhuniBuilder.h"

namespace TOOBAD4ML {

namespace ASTTraversal {

class ExtractVulnerabilitiesVistorTest:
    public ::testing::Test {

protected:

    void SetUp() override {
        description::cPadmanabhuniBuilder pmd;
        clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());

        std::vector<std::string> Sources;
        Sources.push_back("../../../data/testEmpty.c");
        Sources.push_back("../../../data/test.c");
        Sources.push_back("../../../data/testSeveral.c");

        clang::tooling::ClangTool Tool(Compilations, Sources);

        std::vector<std::unique_ptr<clang::ASTUnit>> ASTs;
        Tool.buildASTs(ASTs);
        
        ASTEmpty = std::move(ASTs[0]);
        ASTWithVulnerability = std::move(ASTs[1]);
        ASTWithVulnerabilities = std::move(ASTs[2]);
    }


    std::unique_ptr<clang::ASTUnit> ASTEmpty;
    std::unique_ptr<clang::ASTUnit> ASTWithVulnerability;
    std::unique_ptr<clang::ASTUnit> ASTWithVulnerabilities;
};

/**
 * The name of the file that AST simulates in function buildASTFromCode is : input.cc
 */

TEST_F(ExtractVulnerabilitiesVistorTest, NoVulnerableLines) {
    cExtractVulnerabilitiesVisitor visitor(ASTEmpty.get()->getASTContext());
    cExtractVulnerabilitiesVisitorTest helper;
    std::vector<BOFLocation> vulnLines = helper.getVulnerableLines(visitor);
    EXPECT_EQ(vulnLines.size(), 0);
}

TEST_F(ExtractVulnerabilitiesVistorTest, VulnerableLines) {
    cExtractVulnerabilitiesVisitor visitor(ASTWithVulnerability.get()->getASTContext());
    cExtractVulnerabilitiesVisitorTest helper;
    std::vector<BOFLocation> vulnLines = helper.getVulnerableLines(visitor);
    EXPECT_EQ(vulnLines.size(), 1);

    std::string begin = vulnLines[0].first.printToString(ASTWithVulnerability.get()->getASTContext().getSourceManager());
    std::string end = vulnLines[0].second.printToString(ASTWithVulnerability.get()->getASTContext().getSourceManager());

    EXPECT_EQ("5:1", begin.substr(begin.length() - 3, 3));
    EXPECT_EQ("5:18", end.substr(end.length() - 4, 4));

}

TEST_F(ExtractVulnerabilitiesVistorTest, SeveralVulnerableLines) {
cExtractVulnerabilitiesVisitor visitor(ASTWithVulnerabilities.get()->getASTContext());
    cExtractVulnerabilitiesVisitorTest helper;
    std::vector<BOFLocation> vulnLines = helper.getVulnerableLines(visitor);
    EXPECT_EQ(vulnLines.size(), 2);

    std::vector<std::string> expected = {"6:1", "6:18","5:1", "5:18"};
    int i = 0;
    for (BOFLocation vulnLine: vulnLines) {
        std::string begin = vulnLine.first.printToString(ASTWithVulnerability.get()->getASTContext().getSourceManager());
        std::string end = vulnLine.second.printToString(ASTWithVulnerability.get()->getASTContext().getSourceManager());

        EXPECT_EQ(expected[i], begin.substr(begin.length() - 3, 3));
        EXPECT_EQ(expected[i+1], end.substr(end.length() - 4, 4));
        i += 2;
    }
}

} /* ASTTraversal */

} /* TOOBAD4ML */