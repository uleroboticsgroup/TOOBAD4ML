#include "description/InputValidationClassification.h"


// ----------------------------------------------------------------------------

using namespace TOOBAD4ML;
using namespace description;


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cInputValidationClassification::cInputValidationClassification(
		IDescriptor *decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};


// INHERITED METHODS
// ----------------------------------------------------------------------------

std::string cInputValidationClassification::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof)
{
	std::string decoratedFeature =
        cDescriptorDecorator::ExtractFeature(cpg, bof);

	return decoratedFeature.append("inputValidation..");
}


