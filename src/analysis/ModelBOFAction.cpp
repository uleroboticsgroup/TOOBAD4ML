// ----------------------------------------------------------------------------
#include "analysis/ModelBOFAction.h"
#include "analysis/ModelBOFConsumer.h"
// ----------------------------------------------------------------------------
#include <clang/Frontend/CompilerInstance.h>
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace analysis;
// ----------------------------------------------------------------------------


// clang::FrontendAction INHERITED METHODS
// ----------------------------------------------------------------------------

std::unique_ptr<clang::ASTConsumer> cModelBOFAction::CreateASTConsumer(
		clang::CompilerInstance& CI, llvm::StringRef InFile) {
	return std::unique_ptr<clang::ASTConsumer>(
			new cModelBOFConsumer(&CI.getASTContext()));
}
