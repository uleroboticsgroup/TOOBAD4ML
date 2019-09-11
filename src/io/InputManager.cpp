#include <llvm/Support/CommandLine.h>
#include <clang/Tooling/Tooling.h>
#include "io/InputManager.h"
#include "io/CmdLineArguments.h"
#include "io/Logger.h"
// ------------------------------------------------------------------------
#include <iostream>
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace IO;

// CLASS METHODS
// ------------------------------------------------------------------------
sCmdLineArguments& cInputManager::GetSourceFromCommandLine(int argc, const char** argv) {
    IO::cLogger* logger = IO::cLogger::GetInstance();

    // define the arguments to be extracted
    llvm::cl::list<std::string> sources(
            llvm::cl::Positional,
            llvm::cl::desc("<source0> [...<sourceN>]"),
            llvm::cl::OneOrMore
    );
    llvm::cl::opt<std::string> logLevel("l", llvm::cl::desc("Specify log level: \n\tDEBUG\n\tINFO\n\tWARN\n\tERROR\n\tFATAL"));

    llvm::cl::opt<std::string> Descriptor("d", llvm::cl::desc("Specify descriptor: \n\tPadmanabhuni"), llvm::cl::Required);

    llvm::cl::opt<std::string> OutputFilename("o",  llvm::cl::desc("Specify output filename"),  llvm::cl::value_desc("filename"));

    llvm::cl::opt<std::string> OutputFormat("f",  llvm::cl::desc("Specify output format: \n\tSTD \n\tCSV\n Default output is standard output."),
    llvm::cl::init("STD"), llvm::cl::value_desc("format"));

    llvm::cl::ParseCommandLineOptions(argc, argv);
    
    std::map<eFlagsType, std::string> flags;

    if (logLevel.getValue() != "") {
        if(!logger->SetLogLevel(logLevel.getValue())) {
            std::cout << "Log level not valid. Using INFO level.\n";
            logger->Write(IO::eLogLevel::WARN, "Log level not valid. Using INFO level.");
        }
    }

    logger->Write(IO::eLogLevel::INFO, "User input:");

    flags.insert(std::make_pair(eFlagsType::OUTPUT_EXTENSION, OutputFormat.getValue()));
    logger->Write(IO::eLogLevel::INFO, "Output extension type:   " +  OutputFormat.getValue());

    if (OutputFormat.getValue() != "STD") {
        flags.insert(std::make_pair(eFlagsType::OUTPUT_FILENAME, OutputFilename.getValue()));
        logger->Write(IO::eLogLevel::INFO, "Output file name:        " +  OutputFilename.getValue());
    }
    else {
        if (OutputFilename.getValue() != ""){
            logger->Write(IO::eLogLevel::WARN, "Output type not specified. Using standard output");
            std::cout << "Output type not specified. Using standard output" << "\n\n";
        } 

        flags.insert(std::make_pair(eFlagsType::OUTPUT_FILENAME, ""));     
    }

    flags.insert(std::make_pair(eFlagsType::DESCRIPTOR_SET, Descriptor.getValue()));
    logger->Write(IO::eLogLevel::INFO, "Descriptor selected:     " +  Descriptor.getValue());

    sCmdLineArguments *cmdLine = new sCmdLineArguments(sources, flags);
    return *cmdLine;
    
}

std::unique_ptr<clang::tooling::CompilationDatabase>
cInputManager::GetCompilationDatabase(const llvm::Twine& source) {
    std::string errorMessage;

    // check if the source (file) has a compilation database
    auto compilationDB =
        clang::tooling::CompilationDatabase::autoDetectFromSource(
                source.str(), errorMessage
    );

    // or if the source (directory) has a compilation database
    if (!compilationDB) {
        compilationDB =
            clang::tooling::CompilationDatabase::autoDetectFromDirectory(
                    source.str(), errorMessage
        );
    }

    // otherwise, create an empty compilation database
    if (!compilationDB && !errorMessage.empty()) {
        compilationDB.reset(new clang::tooling::FixedCompilationDatabase(
                ".", std::vector<std::string>()
        ));
    }

    return compilationDB;
}
