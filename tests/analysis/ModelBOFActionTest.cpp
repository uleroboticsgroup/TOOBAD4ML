#include <gtest/gtest.h>
#include "clang/Tooling/Tooling.h"
#include "analysis/ModelBOFAction.h"
#include "analysis/ModelBOFConsumer.h"
#include "clang/Frontend/CompilerInstance.h"
#include "ModelBOFActionTestHelper.h"
#include "description/DescriptorFactory.h"
#include <iostream>
// ----------------------------------------------------------------------------
// TODO Create a directory with tests files.



namespace TOOBAD4ML {

namespace analysis {

class BOFActionTest : public ::testing::Test{

protected:
    void SetUp() override {
        description::cDescriptorFactory descriptorFactory;
        action = new cModelBOFAction(descriptorFactory.CreateDescriptor("Padmanabhuni"));
    }

    cModelBOFAction* action;
};


TEST_F(BOFActionTest, CreateASTConsumer) {
    clang::CompilerInstance ci;
    llvm::StringRef file("test");
    ci.createDiagnostics();
    description::cDescriptorFactory descriptorFactory;
    cModelBOFActionTestHelper helper(descriptorFactory.CreateDescriptor("Padmanabhuni"));
    clang::ASTConsumer* generatedConsumer = helper.CreateASTConsumerTestHelper(ci, file).get();
    EXPECT_EQ(helper.getModelBOFConsumer(), generatedConsumer);
};

} /* TOOBAD4ML */

} /* analysis */