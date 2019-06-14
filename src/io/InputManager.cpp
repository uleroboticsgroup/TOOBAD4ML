#include <llvm/Support/CommandLine.h>
#include <clang/Tooling/Tooling.h>
#include "io/InputManager.h"

using namespace TOOBAD4ML;
using namespace IO;

/*
* Parses the command line arguments to get the source.
*
* @param argc   Number of command-line arguments. It must be greater than
*               1 because the binary already counts as an argument.
* @param argv   List of command-line arguments, including program's name,
*               sources and/or options.
* @returns Source path.
*/
std::vector<std::string> InputManager::GetSourceFromCommandLine(int argc, const char** argv) {
    // define the arguments to be extracted
    llvm::cl::list<std::string> sources(
            llvm::cl::Positional,
            llvm::cl::desc("<source0> [...<sourceN>]"),
            llvm::cl::OneOrMore
    );
    llvm::cl::ParseCommandLineOptions(argc, argv);

    return sources;
}

/*
* Retrieves the compilation database from a source.
*
* @param source    Source path.
* @returns A reference to the corresponding compilation database.
*/
std::unique_ptr<clang::tooling::CompilationDatabase>
InputManager::GetCompilationDatabase(const llvm::Twine& source) {
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
