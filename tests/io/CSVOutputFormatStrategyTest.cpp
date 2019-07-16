#include "gtest/gtest.h"

#include "io/CSVOutputFormatStrategy.h"
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/APFloat.h>

using namespace TOOBAD4ML;
using namespace IO;

class CSVOutputFormatStrategyFactory
: public ::testing::Test {

protected:
    void SetUp() override{
        strategy = new cCSVOutputFormatStrategy();

    }

    cCSVOutputFormatStrategy* strategy;
};

TEST_F(CSVOutputFormatStrategyFactory, Write) {
    std::string output; 
    llvm::raw_string_ostream stream(output);

    std::vector<std::string> descriptor;
    descriptor.push_back("line test 1");
    descriptor.push_back("line test 2");
    strategy->Write(stream, descriptor);
    EXPECT_EQ("line test 1\nline test 2\n", stream.str());
}
