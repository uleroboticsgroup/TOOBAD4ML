#include "description/File.h"
#include "description/BufferOverflow.h"

// ----------------------------------------------------------------------------

using namespace TOOBAD4ML;
using namespace description;


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cFile::cFile(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------

std::string cFile::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
	std::vector<std::string> fileFunctions {"fscanf", "fgetc", "fgets"};
	int counter = 0;

	for (clang::CallExpr* inputCallExpr: bof.GetInput()) {
		std::vector<std::string>::iterator inputIt = std::find(fileFunctions.begin(), fileFunctions.end(), inputCallExpr->getDirectCallee()->getNameAsString());

		if (inputIt != fileFunctions.end()) {
			counter++;
		}
	}

	return decoratedFeature.append(std::to_string(counter).append(cDescriptorDecorator::FEATURE_SEPARATOR));
}
