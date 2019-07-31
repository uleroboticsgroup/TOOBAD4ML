#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "analysis/ModelBOFConsumer.h"
#include "clang/Frontend/ASTUnit.h"
#include "description/PadmanabhuniBuilder.h"
#include "clang/Tooling/CompilationDatabase.h"

// ----------------------------------------------------------------------------

namespace TOOBAD4ML {

namespace analysis {

TEST(BOFConsumer, HandleTranslationUnit) {
    description::cPadmanabhuniBuilder pmd;
    clang::tooling::FixedCompilationDatabase Compilations("/", std::vector<std::string>());

    std::vector<std::string> Sources;
    Sources.push_back("data/test.c");
    clang::tooling::ClangTool Tool(Compilations, Sources);
    Tool.setDiagnosticConsumer(new clang::IgnoringDiagConsumer());

    std::vector<std::unique_ptr<clang::ASTUnit>> ASTs;
    Tool.buildASTs(ASTs);

    std::unique_ptr<clang::ASTUnit> AST = std::move(ASTs[0]);
    cModelBOFConsumer consumer(*(pmd.CreateDescriptor()));
    consumer.HandleTranslationUnit(AST.get()->getASTContext());

    cModelBOFConsumerTest helper;
    std::vector<std::string> dataset = helper.getDataset(consumer);
    EXPECT_EQ(dataset.size(), 1);
    EXPECT_EQ(dataset[0], "5;1;0;0;0;-1;-1;-1;-1;-1;0;");
}

TEST(BOFConsumer, Constructor) {
    description::cPadmanabhuniBuilder pmd;
    std::unique_ptr<cModelBOFConsumer> consumer(new cModelBOFConsumer(*(pmd.CreateDescriptor())));
    EXPECT_NE(consumer, nullptr);
}


} /* TOOBAD4ML */

} /* analysis */