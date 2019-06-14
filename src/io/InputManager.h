#ifndef IO_INPUTMANAGER_H
#define IO_INPUTMANAGER_H
#include <vector>
#include <iostream>
#include <memory>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>


namespace TOOBAD4ML {

namespace IO {

class InputManager {

public:
    InputManager();

    static std::vector<std::string> GetSourceFromCommandLine(int argc, const char** argv);

    static std::unique_ptr<clang::tooling::CompilationDatabase>
    GetCompilationDatabase(const llvm::Twine& source);

};

}

}
#endif