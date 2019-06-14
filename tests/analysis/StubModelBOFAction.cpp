#include "StubModelBOFAction.h"
#include "analysis/MockModelBOFConsumer.h"
#include <clang/Frontend/CompilerInstance.h>

using namespace TOOBAD4ML;
using namespace analysis;

cStubModelBOFAction::cStubModelBOFAction() : m_consumer(nullptr){}

/*!
 *
 *
 * @param
 * @param
 * @return
 */
std::unique_ptr<clang::ASTConsumer> cStubModelBOFAction::CreateASTConsumer(
        clang::CompilerInstance& CI, llvm::StringRef) {
        return std::move(consumer);
}
