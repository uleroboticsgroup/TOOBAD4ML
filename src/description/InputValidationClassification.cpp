#include "description/InputValidationClassification.h"

using namespace TOOBAD4ML;
using namespace description;

cInputValidationClassification::cInputValidationClassification(
		IFeatureExtractor *decoratedComponent) :
		cFeatureExtractorDecorator(decoratedComponent) {
};

llvm::StringRef cInputValidationClassification::ExtractFeature(cCodePseudoPropertyGraph &cppg, cBufferOverflow &bufferOverflow)
{
	std::string decoratedFeature = cFeatureExtractorDecorator::ExtractFeature(cppg, bufferOverflow);

	return decoratedFeature + "sinkClassi..";
}


