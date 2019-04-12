// ----------------------------------------------------------------------------
#ifndef  TOOBAD4ML_ANALYSIS_MODELBOFACTION_H
#define  TOOBAD4ML_ANALYSIS_MODELBOFACTION_H
// ----------------------------------------------------------------------------
#include <clang/Frontend/FrontendAction.h>
// ----------------------------------------------------------------------------


namespace TOOBAD4ML {

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

protected:

	/*!
     * Create the AST consumer object for this action.
	 *
	 * @param CI
	 * @param InFile
	 * @return a new AST consumer; null on failure.
	 */
	std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
			clang::CompilerInstance&, llvm::StringRef) override;

}; /* class cModelBOFAction */

} // namespace analysis

} // namespace TOOBAD4ML

// ----------------------------------------------------------------------------
#endif
