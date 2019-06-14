#ifndef STUBMODELBOFACTION_H
#define STUBMODELBOFACTION_H

#include <clang/Frontend/FrontendAction.h>

#include "analysis/MockModelBOFConsumer.h"

namespace TOOBAD4ML {

namespace analysis {

/*!
 * Stub class to create a mock ModelBOFConsumer.
 */
class cStubModelBOFAction :
    public clang::ASTFrontendAction {

public:
    explicit cStubModelBOFAction(std::unique_ptr<clang::ASTConsumer> mockedConsumer):
        consumer(std::move(mockedConsumer)) {}

protected:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance&, llvm::StringRef) override;

private:
    std::unique_ptr<clang::ASTConsumer> consumer;

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
