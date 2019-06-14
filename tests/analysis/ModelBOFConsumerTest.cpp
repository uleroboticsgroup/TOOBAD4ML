#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "analysis/ModelBOFConsumer.h"
#include "clang/Frontend/ASTUnit.h"
// ----------------------------------------------------------------------------

namespace TOOBAD4ML {

namespace analysis {

TEST(BOFConsumer, HandleTranslationUnit) {
    std::string code = "#include <stdio.h>\nvoid echo(){\nchar buffer[256];\nprintf(\"Type your input:\n\");\ngets(\"%s\", buffer);\ngets(\"%s\", buffer);\ngets(\"%s\", buffer);\nprintf(\"Input given: %s\n\", buffer);\n}\nint main(){\necho();\nreturn 0;\n}\n\n/// ###BEGIN_VULNERABLE_LINES###\n\n/// 5,1;5,18\n\n/// 6,1;6,18\n\n/// 6,1;6,18\n";

    std::unique_ptr<clang::ASTUnit> AST = std::move(clang::tooling::buildASTFromCode(code));
    clang::ASTContext& context = AST.get()->getASTContext();
    cModelBOFConsumer consumer(&context);
    consumer.HandleTranslationUnit(&context);
}

/* 

TEST(BOFConsumer, constructor) {
    clang::ASTContext *context = &(clang::tooling::buildASTFromCode("").get()->getASTContext());
    std::unique_ptr<cModelBOFConsumer> consumer(new cModelBOFConsumer(context));
    EXPECT_NE(consumer.get(), nullptr);
};

*/

} /* TOOBAD4ML */

} /* analysis */