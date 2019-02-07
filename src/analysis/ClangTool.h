#ifndef TOOBAD4ML_ANALYSIS_CLANGTOOL_H
#define TOOBAD4ML_ANALYSIS_CLANGTOOL_H

#include <clang/Tooling/Tooling.h>


namespace TOOBAD4ML {

namespace analysis {

/*!
 * Utility to run a <CODE>clang::FrontendAction</CODE> over a list of files.
 *
 * This class is a wrapper for <CODE>clang::tooling::ClangTool</CODE> in order
 * to facilitate the creation of such tool either by command-line arguments or
 * by a fixed resource (file or directory).
 */
class cClangTool {
public:

    /*!
     * Creates an utility to run actions over a list of files.
     *
     * @param argc Number of command line arguments containing paths (must be
     *             greater than 1).
     * @param argv List of paths containing resources (either files or
     *             directories).
     */
    cClangTool(int, const char**);

    /*!
     * Creates an utility to run actions over a list of files.
     *
     * @param path A path containing a single resource (either a file or a
     *             directory).
     */
    cClangTool(const llvm::Twine&);

    ~cClangTool();

    /*!
     * Runs an action over a list of files.
     *
     * @param action Tool action.
     * @returns 0 on success; 1 if any error occurred; 2 if there is no error
     *          but some files are skipped due to missing compile commands.
     */
    int Run(clang::tooling::ToolAction*);

private:

    /// Tool to run actions.
    clang::tooling::ClangTool* m_tool;

}; /* cClangTool */

} /* analysis */

} /* TOOBAD4ML */

#endif /* TOOBAD4ML_ANALYSIS_CLANGTOOL_H */
