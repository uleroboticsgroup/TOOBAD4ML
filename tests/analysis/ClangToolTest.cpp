#include <gtest/gtest.h>

#include "analysis/ClangTool.h"
#include "analysis/ModelBOFAction.h"


TEST(analysis_test, ClangToolBoot) {

    // 1.
    std::vector<std::string> sources;
    sources.push_back("test.c");

    // 2.
    TOOBAD4ML::analysis::cClangTool tool(0, NULL, sources);

    // 3.
    EXPECT_EQ(1, tool.Run(
         clang::tooling::newFrontendActionFactory<
                            TOOBAD4ML::analysis::cModelBOFAction>().get())
    );

}
