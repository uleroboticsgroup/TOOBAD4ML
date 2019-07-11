#include "description/BufferOverflow.h"
#include "ResetsInControlPredicates.h"

using namespace TOOBAD4ML;

using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cResetsInControlPredicates::cResetsInControlPredicates(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
}
;

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cResetsInControlPredicates::ExtractFeature(cCodePropertyGraph &cpg,
		cBufferOverflow &bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg,
			bof);

	std::string feature = "0";






	return decoratedFeature.append(feature).append(
			cDescriptorDecorator::FEATURE_SEPARATOR);
}
