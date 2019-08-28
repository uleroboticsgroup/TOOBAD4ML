#include <gtest/gtest.h>
#include "description/DescriptorFactory.h"
#include "clang/Tooling/Tooling.h"
#include "description/PadmanabhuniBuilder.h"
#include "description/Descriptor.h"

namespace TOOBAD4ML{

namespace description{

class DescriptorFactoryTest: 
    public ::testing::Test {

protected:

    void SetUp() override {
        factory = new cDescriptorFactory();
    }

    cDescriptorFactory* factory;
};

TEST_F(DescriptorFactoryTest, UNKNOWN) {
    ASSERT_TRUE(nullptr == factory->CreateDescriptor("?"));
}

TEST_F(DescriptorFactoryTest, PADMANABHUNI) {
    ASSERT_TRUE(nullptr != factory->CreateDescriptor("Padmanabhuni"));
}

}

}
