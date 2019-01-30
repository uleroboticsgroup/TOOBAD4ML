#include "analysis/ClangTool.h"

using namespace TOOBAD4ML;
using namespace analysis;

//TODO: To complete with our own args
static llvm::cl::OptionCategory MyToolCategory("MY GOD");


/*!
 *
 *
 * @param
 * @param
 * @param
 */
cClangTool::cClangTool(
        int argc,
        const char **argv,
        std::vector<std::string> sources) :
    m_optionsParser(argc, argv, MyToolCategory),
    m_tool(NULL) {

        std::vector<std::string> sourcePathList =
            (argc > 0) ? m_optionsParser.getSourcePathList() : sources;

        m_tool = new clang::tooling::ClangTool(
                m_optionsParser.getCompilations(),
                sourcePathList);
}


/*!
 *
 */
cClangTool::~cClangTool() {
    delete m_tool;
}


/*!
 *
 * @param
 *
 * @return
 */
int cClangTool::Run(clang::tooling::ToolAction* action) {
    return m_tool->run(action);
}
