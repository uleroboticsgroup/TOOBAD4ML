// ----------------------------------------------------------------------------
#include "analysis/ModelBOFAction.h"
#include "analysis/ModelBOFConsumer.h"
// ----------------------------------------------------------------------------
#include "description/PadmanabhuniBuilder.h"
//----------------------------------------------------------------------------
#include <clang/Frontend/CompilerInstance.h>
#include <iostream>
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace analysis;
// ----------------------------------------------------------------------------


// clang::FrontendAction INHERITED METHODS
// ----------------------------------------------------------------------------

std::unique_ptr<clang::ASTConsumer> cModelBOFAction::CreateASTConsumer(
		clang::CompilerInstance& CI, llvm::StringRef) {
    // create a descriptive model by default
	description::cPadmanabhuniBuilder pmd;
	
	CI.getDiagnostics().setClient(new clang::IgnoringDiagConsumer());

	cModelBOFConsumer* BOFconsumer = new cModelBOFConsumer(*(pmd.CreateDescriptor()));
	m_modelBOFConsumer = BOFconsumer;
	return std::unique_ptr<clang::ASTConsumer>(BOFconsumer);
}

cModelBOFConsumer* cModelBOFAction::getModelBOFConsumer() {
	return m_modelBOFConsumer;
};
