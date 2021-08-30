#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include "stdio.h"
#include <string>
#include "io/Logger.h"

using namespace TOOBAD4ML;
using namespace IO;

class LoggerTest
: public ::testing::Test {

protected:
    void SetUp() override{
        logger = cLogger::GetInstance();
    }

    cLogger* logger;
};

TEST_F(LoggerTest, GetInstance) {
    EXPECT_NE(nullptr, logger);
    EXPECT_EQ(logger, cLogger::GetInstance());
}

TEST_F(LoggerTest, BelowLevel) {
    std::ifstream myfile;
    logger->SetLogLevel("INFO");
    logger->SetFilename("toobad4ml_test.log");
    logger->Write(eLogLevel::DEBUG, "Test");
    myfile.open("toobad4ml_test.log");    
    std::string line;
    
    std::getline(myfile, line);
    EXPECT_EQ("", line);

    myfile.close();

    std::remove("toobad4ml_test.log");
}

TEST_F(LoggerTest, SameLevel) {
    std::ifstream myfile;
    logger->SetLogLevel("INFO");
    logger->SetFilename("toobad4ml_test.log");
    logger->Write(eLogLevel::INFO, "Test");
    myfile.open("toobad4ml_test.log");    
    std::string line;
    
    std::getline(myfile, line);
    EXPECT_EQ("INFO   Test", line.substr(20));

    myfile.close();

    std::remove("toobad4ml_test.log");
}

TEST_F(LoggerTest, UpperLevel) {
    std::ifstream myfile;
    logger->SetLogLevel("INFO");
    logger->SetFilename("toobad4ml_test.log");
    logger->Write(eLogLevel::ERROR, "Test");
    myfile.open("toobad4ml_test.log");    
    std::string line;
    
    std::getline(myfile, line);
    EXPECT_EQ("ERROR  Test", line.substr(20));

    myfile.close();

    std::remove("toobad4ml_test.log");
}