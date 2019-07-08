#ifndef IO_INPUTMANAGER_H
#define IO_INPUTMANAGER_H
#include <clang/Tooling/Tooling.h>
#include "CmdLineArguments.h"

namespace TOOBAD4ML {

namespace IO {

class cInputManager {

public:    
    sCmdLineArguments& GetSourceFromCommandLine(int, const char**);

    std::unique_ptr<clang::tooling::CompilationDatabase>
    GetCompilationDatabase(const llvm::Twine&);

};

}

}
#endif