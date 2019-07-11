#ifndef IO_INPUTMANAGER_H
#define IO_INPUTMANAGER_H
#include <clang/Tooling/Tooling.h>
#include "CmdLineArguments.h"

namespace TOOBAD4ML {

namespace IO {

/*!
 * \class cInputManager
 *
 * \brief
 * A utility to read and process the arguments of the program.
 *
 */
class cInputManager {

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------
public:    
    sCmdLineArguments& GetSourceFromCommandLine(int, const char**);

    // CLASS METHODS
    // ------------------------------------------------------------------------
public:
    std::unique_ptr<clang::tooling::CompilationDatabase>
    GetCompilationDatabase(const llvm::Twine&);

};

} /* IO */

} /* TOOBAD4ML */

#endif