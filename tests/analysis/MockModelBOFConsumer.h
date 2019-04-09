#ifndef MOCKMODELBOFCONSUMER_H
#define MOCKMODELBOFCONSUMER_H

#include <analysis/ModelBOFConsumer.h>

#include <gmock/gmock.h>

namespace TOOBAD4ML {

namespace analysis {

/*!
 *
 */
class cMockModelBOFConsumer : public cModelBOFConsumer {
public:
	cMockModelBOFConsumer(clang::ASTContext*);

    MOCK_METHOD1(HandleTranslationUnit, void(clang::ASTContext*));
    MOCK_METHOD0(Output, bool());

}; /* cMockModelBOFConsumer */

} /* analysis */

} /* TOOBAD4ML */

#endif /* MOCKMODELBOFCONSUMER_H */
