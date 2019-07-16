#include "gtest/gtest.h"
#include "io/FormatStrategyFactory.h"

#include "io/CSVOutputFormatStrategy.h"
#include "io/IOutputFormatStrategy.h"
#include "io/STDOutputFormatStrategy.h"
#include "type_traits"

using namespace TOOBAD4ML;
using namespace IO;

class FormatStrategyFactoryTest
: public ::testing::Test {

protected:
    void SetUp() override{
        factory = new cFormatStrategyFactory();

    }

    cFormatStrategyFactory* factory;
};
/*
TEST_F(FormatStrategyFactoryTest, CreateCSVOutputFormatStrategy) {
    EXPECT_EQ(typeid(cCSVOutputFormatStrategy), typeid(std::result_of<factory->CreateCSVOutputFormatStrategy()>::type));
}

TEST_F(FormatStrategyFactoryTest, CreateSTDOutputFormatStrategy) {
    EXPECT_EQ(typeid(cSTDOutputFormatStrategy), typeid(std::result_of<factory->CreateSTDOutputFormatStrategy()>::type));
}

*/

TEST_F(FormatStrategyFactoryTest, getOutputFormatTypeSTD) {
    EXPECT_EQ(eOutputFormatType::CSV, factory->getOutputFormatType("CSV"));
}

TEST_F(FormatStrategyFactoryTest, getOutputFormatTypeCSV) {
    EXPECT_EQ(eOutputFormatType::STD, factory->getOutputFormatType("STD"));
}

TEST_F(FormatStrategyFactoryTest, getOutputFormatTypeUnknown) {
    EXPECT_EQ(eOutputFormatType::STD, factory->getOutputFormatType("UNK"));
}