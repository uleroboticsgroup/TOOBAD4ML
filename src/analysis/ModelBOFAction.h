// ----------------------------------------------------------------------------
#ifndef  TOOBAD4ML_ANALYSIS_MODELBOFACTION_H
#define  TOOBAD4ML_ANALYSIS_MODELBOFACTION_H
// ----------------------------------------------------------------------------
#include <clang/Frontend/FrontendAction.h>
#include "ModelBOFConsumer.h"
#include "llvm/ADT/Twine.h"
#include "io/CmdLineArguments.h"
#include <iostream>
// ----------------------------------------------------------------------------


namespace TOOBAD4ML {

namespace IO {
	class IOutputFormatStrategy;
}

namespace analysis {

/*!
 * \class cModelBOFAction
 *
 * \brief
 * Executes the frontend action for extracting BOF characteristics.
 *
 * \details
 * This class takes care of executing a specific action in Clang's frontend.
 * Particularly, it creates a <TOOBAD4ML::analysis::ModelBOFConsumer>, for
 * extracting BOF characteristics.
 *
 * NOTE. Check this link! http://my-classes.com/2014/07/01/working-with-ast-matcher-without-clangtool-compilation-database/
 */
class cModelBOFAction: public clang::ASTFrontendAction {

    // clang::FrontendAction INHERITED METHODS
    // ------------------------------------------------------------------------
public:
	cModelBOFConsumer* getModelBOFConsumer();
	void setCmdLineArguments(IO::sCmdLineArguments&);
protected:

	void EndSourceFileAction() override;
	/*!
     * Create the AST consumer object for this action.
	 *
	 * @param CI        Not used.
	 * @param InFile    Not used.
	 * @return a new AST consumer; null on failure.
	 */
	std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
			clang::CompilerInstance&, llvm::StringRef) override;
	
private:
	std::unique_ptr<IO::sCmdLineArguments> m_cmdLineArguments;
	cModelBOFConsumer* m_modelBOFConsumer;
}; /* class cModelBOFAction */

} // namespace analysis

} // namespace TOOBAD4ML

// ----------------------------------------------------------------------------
#endif
