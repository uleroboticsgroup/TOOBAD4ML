#include "analysis/ClangTool.h"
#include "analysis/ModelBOFAction.h"


/*!
 *
 *
 * @param
 * @param
 *
 * @return
 */
int main(int argc, const char **argv) {
    return TOOBAD4ML::analysis::cClangTool(
            argc, argv, std::vector<std::string>())
        .Run(
             clang::tooling::newFrontendActionFactory<
                            TOOBAD4ML::analysis::cModelBOFAction>().get()
    );
}
