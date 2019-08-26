#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "analysis/ModelBOFFrontendActionFactory.h"
#include "analysis/ModelBOFAction.h"
#include "description/DescriptorFactory.h"
// ----------------------------------------------------------------------------

namespace TOOBAD4ML {

namespace analysis {

class ModelBOFFrontendActionFactoryTest
    : public ::testing::Test {

protected:
    void SetUp() override {
        description::cDescriptorFactory descriptorFactory;
        action = new cModelBOFAction(descriptorFactory.CreateDescriptor("Padmanabhuni"));
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