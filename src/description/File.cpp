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

	int counter = 0;
	std::vector<clang::CallExpr*> input = bof.GetInput();
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
	std::vector<std::string> inputClassificationtypes {"fscanf", "fgetc", "fgets"}; // Command line

	for (std::vector<clang::CallExpr*>::iterator it = input.begin();
			it != input.end(); it++) {
		if (std::find(inputClassificationtypes.begin(), inputClassificationtypes.end(),
				(*it)->getDirectCallee()->getNameAsString()) != inputClassificationtypes.end())
		{
			counter++;
		}
	}
	return decoratedFeature.append(std::to_string(counter).append(cDescriptorDecorator::FEATURE_SEPARATOR));
}
