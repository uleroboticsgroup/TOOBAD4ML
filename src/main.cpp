#include "analysis/ClangTool.h"
#include "analysis/ModelBOFAction.h"


int main(int argc, const char **argv) {
    TOOBAD4ML::analysis::cClangTool tool(argc, argv);

    return tool.Run(
             clang::tooling::newFrontendActionFactory<
                            TOOBAD4ML::analysis::cModelBOFAction>().get()
    );
}
