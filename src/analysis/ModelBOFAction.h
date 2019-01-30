#ifndef  SRC_CORE_MODEL_BOF_ACTION_H_
#define  SRC_CORE_MODEL_BOF_ACTION_H_

#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/CompilerInstance.h>

namespace TOOBAD4ML {

namespace analysis {

/*!
 *
 */
class cModelBOFAction: public clang::ASTFrontendAction {
protected:

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
			clang::CompilerInstance&, llvm::StringRef) override;

};
/* class cModelBOFAction */

} /* namespace analysis */

} /* namespace TOOBAD4ML */

#endif /*  SRC_CORE_MODEL_BOF_ACTION_H_ */
