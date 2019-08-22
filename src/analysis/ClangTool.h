// ----------------------------------------------------------------------------
#ifndef TOOBAD4ML_ANALYSIS_CLANGTOOL_H
#define TOOBAD4ML_ANALYSIS_CLANGTOOL_H
// ----------------------------------------------------------------------------
#include <clang/Tooling/Tooling.h>
#include "io/CmdLineArguments.h"
// ----------------------------------------------------------------------------


namespace TOOBAD4ML {

namespace analysis {
    class cModelBOFAction;


/*!
 * \class cClangTool
 *
 * \brief
 * A utility to run actions over a list of sources within Clang's Frontend.
 *
 * \details
 * This class is a wrapper for <CODE>clang::tooling::ClangTool</CODE>. It
 * facilitates the creation of instances of such class from a compilation
 * database, which can be done either by parsing command-line arguments or by a
 * fixed source (i.e. a file or a directory). A compilation database is a
 * resource used by Clang during the compilation process and is mainly
 * comprised of two things: a set of source files and their related compile
 * options. Likewise, this class wraps the execution of
 * <CODE>clang::FrontendAction</CODE>, which are actions performed by Clang's
 * frontend.
 *
 * NOTE. For the time being, the class only supports actions over
 * a list of files. Support for directories will be added in future releases.
 */
class cClangTool {

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------

public:

    /*!
     * Creates a utility to run frontend actions over a list of sources.
     *
     * @param argc   Number of command-line arguments. It must be greater than
     *               1 because the binary already counts as an argument.
     * @param argv   List of command-line arguments, including: program's name,
     *               list of sources and/or program's options.
     */
    //cClangTool(int, const char**);

    /*!
     * Creates a utility to run frontend actions over a source.
     *
     * @param sources   A list of sources.
     */
    cClangTool(IO::sCmdLineArguments&);

    ~cClangTool();


    // CLASS METHODS
    // ------------------------------------------------------------------------

public:

    /*!
     * Runs an action over the current list of sources.
     *
     * @param action    Tool action.
     * @returns 0 on success; 1 if any error occurred; 2 if there is no error
     *          but some files are skipped due to missing compile commands.
     */
    int Run(clang::tooling::ToolAction*);

    friend class cClangToolTest;

    // ATTRIBUTES
    // ------------------------------------------------------------------------

private:

    //! A compilation database.
    std::unique_ptr<clang::tooling::CompilationDatabase> m_compilationDB;

    //! Tool to run actions.
    std::unique_ptr<clang::tooling::ClangTool> m_tool;

    //! Inline execution arguments
    IO::sCmdLineArguments& m_args;

}; /* class cClangTool */

class cClangToolTest {
public:    
    bool checkIfClangToolExists(cClangTool &tool);

};

} // namespace analysis

} // namespace TOOBAD4ML

// ----------------------------------------------------------------------------
#endif
