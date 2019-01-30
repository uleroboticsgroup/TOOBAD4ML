#include "analysis/ModelBOFAction.h"
#include "analysis/ModelBOFConsumer.h"

using namespace TOOBAD4ML;
using namespace analysis;

std::unique_ptr<clang::ASTConsumer> cModelBOFAction::CreateASTConsumer(
		clang::CompilerInstance& CI, llvm::StringRef) {
	return std::unique_ptr<clang::ASTConsumer>(
			new cModelBOFConsumer(&CI.getASTContext()));
}
