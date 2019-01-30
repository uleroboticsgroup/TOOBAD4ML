#ifndef CLANGTOOL_H
#define CLANGTOOL_H

#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>


namespace TOOBAD4ML {

namespace analysis {

/*!
 *
 */
class cClangTool {
public:

    /*!
     *
     *
     * @param
     * @param
     *
     * @return
     */
    cClangTool(int, const char**, std::vector<std::string>);

    /*!
     *
     */
    ~cClangTool();

    /*!
     *
     *
     * @param
     *
     * @return
     */
    int Run(clang::tooling::ToolAction*);

private:

    ///
    clang::tooling::ClangTool* m_tool;

    ///
    clang::tooling::CommonOptionsParser m_optionsParser;

}; /* cClangTool */

} /* analysis */

} /* TOOBAD4ML */

#endif
