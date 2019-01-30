#include "analysis/StubModelBOFAction.h"
#include "analysis/MockModelBOFConsumer.h"

using namespace TOOBAD4ML;
using namespace analysis;


/*!
 *
 *
 * @param
 * @param
 * @return
 */
std::unique_ptr<clang::ASTConsumer> cStubModelBOFAction::CreateASTConsumer(
            clang::CompilerInstance& CI, llvm::StringRef) {
    return std::unique_ptr<clang::ASTConsumer>(
            new cMockModelBOFConsumer(&CI.getASTContext()));
}
