#include "description/EnvironmentVariable.h"
#include "description/BufferOverflow.h"

// ----------------------------------------------------------------------------

using namespace TOOBAD4ML;
using namespace description;


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cEnvironmentVariable::cEnvironmentVariable(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------

std::string cEnvironmentVariable::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
	std::vector<std::string> envVarFunctions {"getwd", "getcwd"};
	int counter = 0;

	for (clang::CallExpr* inputCallExpr: bof.GetInput()) {
		std::vector<std::string>::iterator inputIt = std::find(envVarFunctions.begin(), envVarFunctions.end(), inputCallExpr->getDirectCallee()->getNameAsString());

		if (inputIt != envVarFunctions.end()) {
			counter++;
		}
	}

	return decoratedFeature.append(std::to_string(counter).append(cDescriptorDecorator::FEATURE_SEPARATOR));
}
