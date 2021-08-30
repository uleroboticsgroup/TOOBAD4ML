// ----------------------------------------------------------------------------
#ifndef  TOOBAD4ML_ANALYSIS_MODELBOFACTION_H
#define  TOOBAD4ML_ANALYSIS_MODELBOFACTION_H
// ----------------------------------------------------------------------------
#include <clang/Frontend/FrontendAction.h>
#include <llvm/ADT/Twine.h>
#include <memory>
// ----------------------------------------------------------------------------
#include "io/CmdLineArguments.h"
// ----------------------------------------------------------------------------


namespace TOOBAD4ML {

namespace description {
	class IDescriptor;
}

namespace IO {
	class IOutputFormatStrategy;
}

namespace analysis {
	class cModelBOFConsumer;
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

    // clang::FrontendAction CLASS METHODS
    // ------------------------------------------------------------------------
public:

	cModelBOFAction(description::IDescriptor *);

	cModelBOFConsumer* getModelBOFConsumer();

	void setCmdLineArguments(IO::sCmdLineArguments&);

	// clang::FrontendAction INHERITED METHODS
    // ------------------------------------------------------------------------
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


   	// ATTRIBUTES
	// ------------------------------------------------------------------------

private:
	//! CMD line arguments
	std::unique_ptr<IO::sCmdLineArguments> m_cmdLineArguments;

	//! The consumer which will be given by the ModelBOFAction
	cModelBOFConsumer* m_modelBOFConsumer;

protected:
	//! The descriptor to be used by the modelBOFConsumer
	description::IDescriptor* m_descriptor;
	
}; /* class cModelBOFAction */

} // namespace analysis

} // namespace TOOBAD4ML

// ----------------------------------------------------------------------------
#endif
