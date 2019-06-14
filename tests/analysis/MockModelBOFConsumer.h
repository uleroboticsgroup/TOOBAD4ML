#ifndef ANALYSIS_MOCKMODELBOFCONSUMER_H_
#define ANALYSIS_MOCKMODELBOFCONSUMER_H_

#include <analysis/ModelBOFConsumer.h>
#include <clang/Frontend/CompilerInstance.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
namespace TOOBAD4ML {

namespace analysis {

/*!
 *
 */
class cMockModelBOFConsumer : public cModelBOFConsumer {
public:
    MOCK_METHOD1(HandleTranslationUnit, void(clang::ASTContext*));
    MOCK_METHOD0(Output, bool());
}; /* cMockModelBOFConsumer */

} /* analysis */

} /* TOOBAD4ML */

#endif