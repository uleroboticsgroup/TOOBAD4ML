#include "VisitorTest.h"

#include "analysis/StubModelBOFAction.h"
#include "analysis/ClangTool.h"

#include <clang/Tooling/Tooling.h>

#include "analysis/MockModelBOFConsumer.h"

namespace TOOBAD4ML {

namespace ASTTraversal {

cVisitorTest::cVisitorTest(): m_findBuffer(nullptr) , m_consumer(nullptr) {

	analysis::cClangTool toolWithData("../data/sinkTypes.c");

	clang::tooling::ToolAction* action = clang::tooling::newFrontendActionFactory<analysis::cStubModelBOFAction>().get();

	std::unique_ptr<clang::tooling::FrontendActionFactory> fact = clang::tooling::newFrontendActionFactory<analysis::cStubModelBOFAction>();

//	toolWithData.Run(action);
//
//	clang::ASTContext &context = fact->create()->getCompilerInstance().getASTContext();
//
//	analysis::cMockModelBOFConsumer consumer(&context);
//
//	m_consumer = consumer;

}

void cVisitorTest::SetUp() {}

void cVisitorTest::TearDown() {}


TEST_F(cVisitorTest, test1) {

	//EXPECT_CALL(m_consumer, HandleTranslationUnit);

}

} /* namespace ASTTraversal */

} /* namespace TOOBAD4ML */
