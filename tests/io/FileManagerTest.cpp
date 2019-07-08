#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include "stdio.h"
#include <string>
#include "io/CSVOutputFormatStrategy.h"
#include "io/STDOutputFormatStrategy.h"
#include "io/FileManager.h"
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/APFloat.h>

using namespace TOOBAD4ML;
using namespace IO;

class FileManagerTest
: public ::testing::Test {

protected:
    void SetUp() override{
        CSVStrategy = new cCSVOutputFormatStrategy();
        STDStrategy = new cSTDOutputFormatStrategy();
        fileManager = cFileManager::GetInstance();
    }

    cCSVOutputFormatStrategy* CSVStrategy;
    cSTDOutputFormatStrategy* STDStrategy;
    cFileManager* fileManager;
};

TEST_F(FileManagerTest, GetInstance) {
    EXPECT_NE(nullptr, fileManager);
    EXPECT_EQ(fileManager, cFileManager::GetInstance());
}


TEST_F(FileManagerTest, WriteFile) {
    std::ifstream myfile;
    std::vector<std::string> descriptor;
    descriptor.push_back("test1");
    descriptor.push_back("test2");
    llvm::Twine file("test.out");
    EXPECT_EQ(true, fileManager->Write(descriptor, CSVStrategy, file, false));

    myfile.open("test.out");    
    std::string line;
    
    std::getline(myfile, line);
    EXPECT_EQ("test1", line);
    
    std::getline(myfile, line);
    EXPECT_EQ("test2", line); 
    myfile.close();

    std::remove("test.out");
}

TEST_F(FileManagerTest, WriteSTD) {
    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

    std::vector<std::string> descriptor;
    descriptor.push_back("test1");
    llvm::Twine file("");
    EXPECT_EQ(true, fileManager->Write(descriptor, STDStrategy, file, false));
    std::string text = buffer.str();
    EXPECT_EQ(text, "test1");
}