#ifndef STUBMODELBOFACTION_H
#define STUBMODELBOFACTION_H

#include <analysis/ModelBOFAction.h>

#include "analysis/MockModelBOFConsumer.h"

namespace TOOBAD4ML {

namespace analysis {

/*!
 * Stub class to create a mock ModelBOFConsumer.
 */
class cStubModelBOFAction :
    public cModelBOFAction {
public:

	cStubModelBOFAction();

    /*!
     *
     *
     * @param
     * @param
     * @return
     */
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance&, llvm::StringRef);

	analysis::cMockModelBOFConsumer* getConsumer(){
		return m_consumer;
	}

	void setConsumer(analysis::cMockModelBOFConsumer* consumer) {
		m_consumer = consumer;
	}

private:
    analysis::cMockModelBOFConsumer *m_consumer;

}; /* cStubModelBOFAction */

} /* analysis */

} /* TOOBAD4ML */

#endif /* STUBMODELBOFACTION_H */
