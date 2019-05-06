#include "description/BufferSizePredicateClassification.h"


using namespace TOOBAD4ML;
using namespace description;


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cBufferSizePredicateClassification::cBufferSizePredicateClassification(
		IDescriptor * decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {

}

// INHERITED METHODS
// ----------------------------------------------------------------------------

std::string cBufferSizePredicateClassification::ExtractFeature(
		cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
        cDescriptorDecorator::ExtractFeature(cpg, bof);

	return decoratedFeature.append("bufferSizePredicateClass;");

}
