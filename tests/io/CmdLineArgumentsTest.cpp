#include "gtest/gtest.h"
#include "io/CmdLineArguments.h"

#include "io/CSVOutputFormatStrategy.h"
#include "io/IOutputFormatStrategy.h"
#include "io/STDOutputFormatStrategy.h"
#include "llvm/Support/Casting.h"

using namespace TOOBAD4ML;
using namespace IO;

class CmdLineArgumentsTest
: public ::testing::Test {

protected:
    void SetUp() override{
        sources.push_back("test1");
        sources.push_back("test2");

        flags.insert(std::make_pair(eFlagsType::OUTPUT_EXTENSION, "STD"));

        flags.insert(std::make_pair(eFlagsType::OUTPUT_FILENAME, "test.out"));

        arguments = new sCmdLineArguments(sources, flags);

    }

    sCmdLineArguments* arguments;
    std::vector<std::string> sources;
    std::map<eFlagsType, std::string> flags;
};

TEST_F(CmdLineArgumentsTest, Constructor) {
    EXPECT_EQ(sources, arguments->getSources());
    EXPECT_EQ(flags, arguments->getFlags());
    EXPECT_EQ(false, arguments->getAppend());
}

TEST_F(CmdLineArgumentsTest, SetSources) {
    std::vector<std::string> sources2;
    sources2.push_back("test3");
    arguments->setSources(sources2);

    EXPECT_EQ(sources2, arguments->getSources());
}

TEST_F(CmdLineArgumentsTest, SetAppend) {
    arguments->setAppend(true);
    EXPECT_EQ(true, arguments->getAppend());
}

TEST_F(CmdLineArgumentsTest, SetFlags) {
    std::map<eFlagsType, std::string> flags2;
    arguments->setFlags(flags2);

    EXPECT_EQ(flags2, arguments->getFlags());
}

TEST_F(CmdLineArgumentsTest, GetFilename) {
    EXPECT_EQ("test.out", arguments->getFilename().str());
}

/*
TEST_F(CmdLineArgumentsTest, GetStrategyCSV) {
    std::map<eFlagsType, std::string> flags2;
    flags2.insert(std::make_pair(eFlagsType::OUTPUT_EXTENSION, "CSV"));
    arguments->setFlags(flags2);

    EXPECT_NE(NULL, llvm::dyn_cast_or_null<cCSVOutputFormatStrategy>(arguments->getStrategy()));
}

TEST_F(CmdLineArgumentsTest, GetStrategySTD) {
    EXPECT_NE(NULL, llvm::dyn_cast_or_null<cSTDOutputFormatStrategy>(arguments->getStrategy()));
}

TEST_F(CmdLineArgumentsTest, GetStrategyUNK) {
    std::map<eFlagsType, std::string> flags2;
    flags2.insert(std::make_pair(eFlagsType::OUTPUT_EXTENSION, "UNK"));
    arguments->setFlags(flags2);

    EXPECT_NE(NULL, llvm::dyn_cast_or_null<cSTDOutputFormatStrategy>(arguments->getStrategy()));
}
*/