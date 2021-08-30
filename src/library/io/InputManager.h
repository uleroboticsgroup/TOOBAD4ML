#ifndef IO_INPUTMANAGER_H
#define IO_INPUTMANAGER_H
// ------------------------------------------------------------------------
#include <clang/Tooling/Tooling.h>
#include "CmdLineArguments.h"
// ------------------------------------------------------------------------
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

    // CLASS METHODS
    // ------------------------------------------------------------------------
public:
    /*
    * Parses the command line arguments to get the source.
    *
    * @param argc   Number of command-line arguments. It must be greater than
    *               1 because the binary already counts as an argsument.
    * @param argv   List of command-line arguments, including program's name,
    *               sources and/or options.
    * @returns Source path.
    */
    sCmdLineArguments& GetSourceFromCommandLine(int, const char**);

    /*
    * Retrieves the compilation database from a source.
    *
    * @param source    Source path.
    * @returns A reference to the corresponding compilation database.
    */
    std::unique_ptr<clang::tooling::CompilationDatabase>
    GetCompilationDatabase(const llvm::Twine&);

};

} /* IO */

} /* TOOBAD4ML */

#endif