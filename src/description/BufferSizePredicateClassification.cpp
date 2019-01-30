#include "description/BufferSizePredicateClassification.h"

using namespace TOOBAD4ML;
using namespace description;

cBufferSizePredicateClassification::cBufferSizePredicateClassification(
		IFeatureExtractor * decoratedComponent) :
		cFeatureExtractorDecorator(decoratedComponent) {

}

llvm::StringRef cBufferSizePredicateClassification::ExtractFeature(
		cCodePseudoPropertyGraph &cppg, cBufferOverflow &bufferOverflow) {

	std::string decoratedFeature = cFeatureExtractorDecorator::ExtractFeature(cppg, bufferOverflow); // delegate to base class

	return decoratedFeature + "buffer"; // extrat Feature BufferSizePredicateClassification

}
