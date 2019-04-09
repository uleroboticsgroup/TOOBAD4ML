#include "CommandLine.h"
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

	int counter = 0;
	std::vector<clang::CallExpr*> input = bof.GetInput();
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
	std::vector<llvm::StringRef> inputClassificationtypes {"scanf", "gets"}; // Command line

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
