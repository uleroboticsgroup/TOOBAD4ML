#include <llvm/Support/CommandLine.h>
#include <clang/Tooling/Tooling.h>
#include "io/InputManager.h"
#include "io/CmdLineArguments.h"
// ------------------------------------------------------------------------
#include <iostream>
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace IO;

// CLASS METHODS
// ------------------------------------------------------------------------
sCmdLineArguments& cInputManager::GetSourceFromCommandLine(int argc, const char** argv) {
    // define the arguments to be extracted
    llvm::cl::list<std::string> sources(
            llvm::cl::Positional,
            llvm::cl::desc("<source0> [...<sourceN>]"),
            llvm::cl::OneOrMore
    );
    llvm::cl::opt<std::string> OutputFilename("o",  llvm::cl::desc("Specify output filename"),  llvm::cl::value_desc("filename"));

    llvm::cl::opt<std::string> OutputFormat("f",  llvm::cl::desc("Specify output format: \n\tSTD \n\tCSV\n Default output is standard output."),
    llvm::cl::init("STD"), llvm::cl::value_desc("format"));

    llvm::cl::ParseCommandLineOptions(argc, argv);
    
    std::map<eFlagsType, std::string> flags;

    flags.insert(std::make_pair(eFlagsType::OUTPUT_EXTENSION, OutputFormat.getValue()));

    if (OutputFormat.getValue() != "STD") {
        flags.insert(std::make_pair(eFlagsType::OUTPUT_FILENAME, OutputFilename.getValue()));
    }
    else {
        if (OutputFilename.getValue() != "") std::cout << "Output type not specified. Using standard output" << "\n\n";

        flags.insert(std::make_pair(eFlagsType::OUTPUT_FILENAME, ""));     
    }


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
