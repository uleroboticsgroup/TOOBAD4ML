#include "description/SinkCharacteristicsClassification.h"


// ----------------------------------------------------------------------------

using namespace TOOBAD4ML;
using namespace description;


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cSinkCharacteristicsClassification::cSinkCharacteristicsClassification(
		IDescriptor *decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};


// INHERITED METHODS
// ----------------------------------------------------------------------------

std::string cSinkCharacteristicsClassification::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof)
{
	std::string decoratedFeature =
        cDescriptorDecorator::ExtractFeature(cpg, bof);

	return decoratedFeature.append("...sinkcharacter..");
}
