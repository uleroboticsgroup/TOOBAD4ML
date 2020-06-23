#include "description/Container.h"
#include "description/BufferOverflow.h"
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cContainer::cContainer(IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cContainer::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
			cDescriptorDecorator::ExtractFeature(cpg, bof);

	std::string feature = "0";
	
	clang::DeclRefExpr* dstBuffer = bof.getBuffer(BufferType::DST);
	clang::Type* dstBufferType = dstBuffer->getDecl()->getType()->getTypePtr();

	if (dstBufferType->isStructureType()) {
		feature = "2";
	}
	else if (dstBufferType->isArrayType()) {
		feature = "1";
	}
	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
