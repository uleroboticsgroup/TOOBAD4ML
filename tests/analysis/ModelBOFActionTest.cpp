#include <gtest/gtest.h>
#include "analysis/ModelBOFAction.h"
#include "analysis/ClangTool.h"
#include "clang/Tooling/Tooling.h"
#include "analysis/ModelBOFConsumer.h"
// ----------------------------------------------------------------------------
// TODO Create a directory with tests files.



namespace TOOBAD4ML {

namespace analysis {


TEST(BOFAction, test1) {
    cModelBOFAction modelBOFAction();
    EXPECT_TRUE(clang::tooling::runToolOnCode(new cModelBOFAction(llvm::make_unique<cModelBOFConsumer>()), "")))
};

} /* TOOBAD4ML */

} /* analysis */