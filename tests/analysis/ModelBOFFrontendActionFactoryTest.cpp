#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "analysis/ModelBOFFrontendActionFactory.h"
#include "analysis/ModelBOFAction.h"
// ----------------------------------------------------------------------------

namespace TOOBAD4ML {

namespace analysis {

class ModelBOFFrontendActionFactoryTest
    : public ::testing::Test {

protected:
    void SetUp() override {
        action = new cModelBOFAction();
        factory = new cModelBOFFrontendActionFactory(*action);
    }

    cModelBOFFrontendActionFactory* factory;
    cModelBOFAction* action;
};

TEST_F(ModelBOFFrontendActionFactoryTest, Constructor) {
    EXPECT_TRUE(factory != nullptr);
}

TEST_F(ModelBOFFrontendActionFactoryTest, Create) {
    EXPECT_EQ(action, factory->create());
}

TEST_F(ModelBOFFrontendActionFactoryTest, GetModelBOFAction) {
    EXPECT_EQ(action, &factory->GetModelBOFAction());
}


} /* TOOBAD4ML */

} /* analysis */