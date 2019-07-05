#include "CmdLineArguments.h"
#include "IOutputFormatStrategy.h"
#include "FormatStrategyFactory.h"

using namespace TOOBAD4ML;
using namespace IO;


std::vector<std::string> sCmdLineArguments::getSources() {
    return m_sources;
}

void sCmdLineArguments::setSources(std::vector<std::string> sources) {
    m_sources = sources;
}

std::map<eFlagsType, std::string> sCmdLineArguments::getFlags() {
    return m_flags;
}
void sCmdLineArguments::setFlags(std::map<eFlagsType, std::string> flags) {
    m_flags = flags;
}

llvm::Twine& sCmdLineArguments::getFilename() {
    llvm::Twine* filename = new llvm::Twine(m_flags.at(IO::eFlagsType::OUTPUT_FILENAME));
    return *filename;
}

IOutputFormatStrategy* sCmdLineArguments::getStrategy() {
    cFormatStrategyFactory* fsFactory = new cFormatStrategyFactory();
    IOutputFormatStrategy* strategy = nullptr;

    eOutputFormatType type = fsFactory->getOutputFormatType(m_flags.at(eFlagsType::OUTPUT_EXTENSION));

    if (type == eOutputFormatType::CSV) {
        strategy = &fsFactory->CreateCSVOutputFormatStrategy(); 
    }
    else{
        strategy = &fsFactory->CreateSTDOutputFormatStrategy();
    }

    return strategy;
}