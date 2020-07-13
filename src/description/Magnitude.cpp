#include "description/Magnitude.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
#include "description/CodePropertyGraph.h"
#include "iostream"
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cMagnitude::cMagnitude(IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cMagnitude::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
			cDescriptorDecorator::ExtractFeature(cpg, bof);

    cExprUtils* utils = cExprUtils::GetInstance();
	std::string feature = std::to_string(utils->guessBufferSize(bof.GetBuffer(BufferType::DST), cpg.GetAST().getASTContext()  ));

	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
