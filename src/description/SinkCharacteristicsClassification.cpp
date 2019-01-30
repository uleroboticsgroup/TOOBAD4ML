#include "description/SinkCharacteristicsClassification.h"

using namespace TOOBAD4ML;
using namespace description;

cSinkCharacteristicsClassification::cSinkCharacteristicsClassification(
		IFeatureExtractor *decoratedComponent) :
		cFeatureExtractorDecorator(decoratedComponent) {
};

llvm::StringRef cSinkCharacteristicsClassification::ExtractFeature(cCodePseudoPropertyGraph &cppg, cBufferOverflow &bufferOverflow)
{
	std::string decoratedFeature = cFeatureExtractorDecorator::ExtractFeature(cppg, bufferOverflow);

	return decoratedFeature + "sinkcharacter..";
}
