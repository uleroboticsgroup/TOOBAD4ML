#ifndef  SRC_CORE_MODEL_BOF_CONSUMER_H_
#define  SRC_CORE_MODEL_BOF_CONSUMER_H_

#include <clang/AST/ASTConsumer.h>
#include <llvm/ADT/StringRef.h>
#include <vector>

namespace TOOBAD4ML {

namespace analysis {

/*!
 *
 */
class cModelBOFConsumer: public clang::ASTConsumer {
public:

	/*!
	 *
     * @param
	 */
	cModelBOFConsumer(clang::ASTContext*);

	/*!
	 *
	 * @param
	 */
	void HandleTranslationUnit(clang::ASTContext&) override;

    /*!
     * TODO: what do we have to return here??
     */
	bool Output();

private:

	//!
	std::vector<std::string> m_dataset;

};

} /* namespace analysis */

} /* namespace TOOBAD4ML */

#endif /*  SRC_CORE_MODEL_BOF_CONSUMER_H_ */
