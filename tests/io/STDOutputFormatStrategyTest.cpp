#include "gtest/gtest.h"
#include "iostream"
#include "io/STDOutputFormatStrategy.h"
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/APFloat.h>

using namespace TOOBAD4ML;
using namespace IO;

class STDOutputFormatStrategyTest
: public ::testing::Test {

protected:
    void SetUp() override{
        strategy = new cSTDOutputFormatStrategy();

    }

    cSTDOutputFormatStrategy* strategy;
};

TEST_F(STDOutputFormatStrategyTest, Write) {
    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

    std::vector<std::string> descriptor;
    descriptor.push_back("test1");
    llvm::Twine file("");
    strategy->Write(llvm::outs(), descriptor);
    std::string text = buffer.str();
    EXPECT_EQ(text, "test1");
}
