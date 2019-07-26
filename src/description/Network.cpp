#include "description/Network.h"
#include "description/BufferOverflow.h"

// ----------------------------------------------------------------------------

using namespace TOOBAD4ML;
using namespace description;


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cNetwork::cNetwork(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------

std::string cNetwork::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
	std::vector<std::string> networkFunctions {"recv", "recvfrom", "recvmsg"};
	int counter = 0;

	for (clang::CallExpr* inputCallExpr: bof.GetInput()) {
		std::vector<std::string>::iterator inputIt = std::find(networkFunctions.begin(), networkFunctions.end(), inputCallExpr->getDirectCallee()->getNameAsString());

		if (inputIt != networkFunctions.end()) {
			counter++;
		}
	}

	return decoratedFeature.append(std::to_string(counter).append(cDescriptorDecorator::FEATURE_SEPARATOR));
}
