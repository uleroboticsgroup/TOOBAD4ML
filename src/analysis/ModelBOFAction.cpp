// ----------------------------------------------------------------------------
#include "analysis/ModelBOFAction.h"
#include "analysis/ModelBOFConsumer.h"
// ----------------------------------------------------------------------------
#include "description/PadmanabhuniBuilder.h"
//----------------------------------------------------------------------------
#include <clang/Frontend/CompilerInstance.h>
#include <iostream>
#include "io/CmdLineArguments.h"
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace analysis;
// ----------------------------------------------------------------------------


// clang::FrontendAction INHERITED METHODS
// ----------------------------------------------------------------------------

std::unique_ptr<clang::ASTConsumer> cModelBOFAction::CreateASTConsumer(
		clang::CompilerInstance& CI, llvm::StringRef file) {
    // create a descriptive model by default
	std::cout << "\nProcessing file " <<  file.str();
	description::cPadmanabhuniBuilder pmd;
	
	CI.getDiagnostics().setClient(new clang::IgnoringDiagConsumer());
	cModelBOFConsumer* BOFconsumer = new cModelBOFConsumer(*(pmd.CreateDescriptor()));
	m_modelBOFConsumer = BOFconsumer;
	return std::unique_ptr<clang::ASTConsumer>(BOFconsumer);
}

cModelBOFConsumer* cModelBOFAction::getModelBOFConsumer() {
	return m_modelBOFConsumer;
};

void cModelBOFAction::setCmdLineArguments(IO::sCmdLineArguments& cmdLineArgs) { 
	m_cmdLineArguments = std::unique_ptr<IO::sCmdLineArguments>(new IO::sCmdLineArguments(cmdLineArgs.getSources(), cmdLineArgs.getFlags()));
};

void cModelBOFAction::EndSourceFileAction() {
	m_modelBOFConsumer->Output(*(m_cmdLineArguments.get()));
};
