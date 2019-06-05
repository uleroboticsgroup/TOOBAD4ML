// ----------------------------------------------------------------------------
#include "analysis/ModelBOFAction.h"
#include "analysis/ModelBOFConsumer.h"
// ----------------------------------------------------------------------------
#include "description/PadmanabhuniBuilder.h"
// ----------------------------------------------------------------------------
#include <clang/Frontend/CompilerInstance.h>
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace analysis;
// ----------------------------------------------------------------------------


// clang::FrontendAction INHERITED METHODS
// ----------------------------------------------------------------------------

std::unique_ptr<clang::ASTConsumer> cModelBOFAction::CreateASTConsumer(
		clang::CompilerInstance&, llvm::StringRef) {
    // create a descriptive model by default
	description::cPadmanabhuniBuilder pmd;

	return std::unique_ptr<clang::ASTConsumer>(
            new cModelBOFConsumer(*(pmd.CreateDescriptor())));
}
