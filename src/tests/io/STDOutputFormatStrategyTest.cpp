#include "gtest/gtest.h"

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
    std::string output; 
    llvm::raw_string_ostream stream(output);

    std::vector<std::string> descriptor;
    descriptor.push_back("line test 1");
    descriptor.push_back("line test 2");
    strategy->Write(stream, descriptor);
    EXPECT_EQ("Results:\nline test 1\nline test 2\n", stream.str());
}
