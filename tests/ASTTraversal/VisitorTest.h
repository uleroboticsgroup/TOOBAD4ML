#include <gtest/gtest.h>

#include "analysis/MockModelBOFConsumer.h"

#ifndef TESTS_ASTTRAVERSAL_FINDBUFFERVISITORTEST_H_
#define TESTS_ASTTRAVERSAL_FINDBUFFERVISITORTEST_H_

namespace TOOBAD4ML {

namespace ASTTraversal {

class cVisitorTest : public testing::Test {
protected:
	cVisitorTest();

	void SetUp() override;

	void TearDown() override;

public:
	analysis::cMockModelBOFConsumer m_consumer;

};

} /* namespace ASTTraversal */

} /* namespace TOOBAD4ML */

#endif /* TESTS_ASTTRAVERSAL_FINDBUFFERVISITORTEST_H_ */
