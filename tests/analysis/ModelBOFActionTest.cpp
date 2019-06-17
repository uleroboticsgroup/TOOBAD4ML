#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "analysis/ModelBOFAction.h"
#include "clang/Frontend/FrontendAction.h"
#include <iostream>
// ----------------------------------------------------------------------------
// TODO Create a directory with tests files.



namespace TOOBAD4ML {

namespace analysis {


TEST(BOFAction, BOFAction) {
    std::unique_ptr<clang::tooling::FrontendActionFactory> frontendFactory = clang::tooling::newFrontendActionFactory<TOOBAD4ML::analysis::cModelBOFAction>();
    std::unique_ptr<clang::FrontendAction> Action(frontendFactory.get()->create());
    ASSERT_TRUE(Action != nullptr);
};

} /* TOOBAD4ML */

} /* analysis */