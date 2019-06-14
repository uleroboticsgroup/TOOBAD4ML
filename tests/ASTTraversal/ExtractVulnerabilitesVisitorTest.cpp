#include <gtest/gtest.h>
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "clang/Frontend/ASTUnit.h"
#include "clang/Tooling/Tooling.h"

namespace TOOBAD4ML {

namespace ASTTraversal {

class ExtractVulnerabilitiesVistorTest:
    public ::testing::Test {

protected:
    ExtractVulnerabilitiesVistorTest(): 
        ASTEmpty(clang::tooling::buildASTFromCode("#include <stdio.h>\nvoid echo(){\nchar buffer[256];\nprintf(\"Type your input:\n\");\nscanf(\"%s\", buffer);\nprintf(\"Input given: %s\n\", buffer);\n}\nint main(){\necho();\nreturn 0;\n}\n\n/// ###BEGIN_VULNERABLE_LINES###\n")),

        ASTWithVulnerability(clang::tooling::buildASTFromCode("#include <stdio.h>\nvoid echo(){\nchar buffer[256];\nprintf(\"Type your input:\n\");\ngets(\"%s\", buffer);\nprintf(\"Input given: %s\n\", buffer);\n}\nint main(){\necho();\nreturn 0;\n}\n\n/// ###BEGIN_VULNERABLE_LINES###\n\n/// 5,1;5,18\n ")),

        ASTWithVulnerabilities(clang::tooling::buildASTFromCode("#include <stdio.h>\nvoid echo(){\nchar buffer[256];\nprintf(\"Type your input:\n\");\ngets(\"%s\", buffer);\ngets(\"%s\", buffer);\ngets(\"%s\", buffer);\nprintf(\"Input given: %s\n\", buffer);\n}\nint main(){\necho();\nreturn 0;\n}\n\n/// ###BEGIN_VULNERABLE_LINES###\n\n/// 5,1;5,18\n\n/// 6,1;6,18\n\n/// 6,1;6,18\n")) {};


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
    // TODO: End column is 4 (?)
    // Only in the first one :: Other lines output right
    for (BOFLocation vulnLine: vulnLines) {
        std::cout << "*********************" << std::endl;
        std::cout << vulnLine.first.printToString(ASTWithVulnerability.get()->getASTContext().getSourceManager()) << std::endl;
        std::cout << vulnLine.second.printToString(ASTWithVulnerability.get()->getASTContext().getSourceManager()) << std::endl;
    }
}

TEST_F(ExtractVulnerabilitiesVistorTest, SeveralVulnerableLines) {
cExtractVulnerabilitiesVisitor visitor(ASTWithVulnerabilities.get()->getASTContext());
    cExtractVulnerabilitiesVisitorTest helper;
    std::vector<BOFLocation> vulnLines = helper.getVulnerableLines(visitor);
    EXPECT_EQ(vulnLines.size(), 2);
    // TODO: End column is 4 (?)
    for (BOFLocation vulnLine: vulnLines) {
        std::cout << "*********************" << std::endl;
        std::cout << vulnLine.first.printToString(ASTWithVulnerabilities.get()->getASTContext().getSourceManager()) << std::endl;
        std::cout << vulnLine.second.printToString(ASTWithVulnerabilities.get()->getASTContext().getSourceManager()) << std::endl;
    }
}

} /* ASTTraversal */

} /* TOOBAD4ML */