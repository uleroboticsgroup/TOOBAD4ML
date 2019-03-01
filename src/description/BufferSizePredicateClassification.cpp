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

llvm::StringRef cBufferSizePredicateClassification::ExtractFeature(
		cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
        cDescriptorDecorator::ExtractFeature(cpg, bof);

	return decoratedFeature + "bufferSizePredicateClass";

}
