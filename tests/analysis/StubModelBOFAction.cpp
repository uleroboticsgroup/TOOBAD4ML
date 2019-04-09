#include "analysis/StubModelBOFAction.h"

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

	 analysis::cMockModelBOFConsumer consumer(&CI.getASTContext());

	 setConsumer(&consumer);


	return std::unique_ptr<clang::ASTConsumer>(&consumer);
}
