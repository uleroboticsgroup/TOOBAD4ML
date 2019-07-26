#include "description/CommandLine.h"
#include "description/BufferOverflow.h"
// ----------------------------------------------------------------------------

using namespace TOOBAD4ML;
using namespace description;


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cCommandLine::cCommandLine(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cCommandLine::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
	std::vector<std::string> commandLineFunctions {"scanf", "gets"};
	int counter = 0;

	for (clang::CallExpr* inputCallExpr: bof.GetInput()) {
		std::vector<std::string>::iterator inputIt = std::find(commandLineFunctions.begin(), commandLineFunctions.end(), inputCallExpr->getDirectCallee()->getNameAsString());

		if (inputIt != commandLineFunctions.end()) {
			counter++;
		}
	}

	return decoratedFeature.append(std::to_string(counter).append(cDescriptorDecorator::FEATURE_SEPARATOR));
}
