#ifndef IO_INPUTMANAGER_H
#define IO_INPUTMANAGER_H
#include <vector>
#include <iostream>
#include <memory>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>
#include "CmdLineArguments.h"

namespace TOOBAD4ML {

namespace IO {

class cInputManager {

public:
    cInputManager();

    static sCmdLineArguments& GetSourceFromCommandLine(int argc, const char** argv);

    static std::unique_ptr<clang::tooling::CompilationDatabase>
    GetCompilationDatabase(const llvm::Twine& source);

};

}

}
#endif