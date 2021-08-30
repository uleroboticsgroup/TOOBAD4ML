#include "description/Container.h"
#include "description/BufferOverflow.h"
#include "iostream"
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

	std::string feature = "-1";
	
	clang::DeclRefExpr* dstBuffer = bof.GetBuffer(BufferType::DST);
	if(dstBuffer) {
		feature = "0";
		const clang::Type* dstBufferType = dstBuffer->getDecl()->getType().getTypePtr();

		if (dstBufferType->isStructureType()) {
			feature = "2";
		}
		else if (dstBufferType->isUnionType()) {
			feature = "3";
		}	
		else if (dstBufferType->isArrayType()) {
			if (clang::dyn_cast_or_null<clang::ArrayType>(dstBufferType)->getElementType()->isStructureType()) {
				feature = "4";

			}
			else if (clang::dyn_cast_or_null<clang::ArrayType>(dstBufferType)->getElementType()->isUnionType()) {
				feature = "5";
			}
			else if (clang::dyn_cast_or_null<clang::ArrayType>(dstBufferType)->getElementType()->isPointerType()){
				feature = "1";
			}
			else if (clang::dyn_cast_or_null<clang::ArrayType>(dstBufferType)->getElementType()->isArrayType()){
				feature = "1";
			}
		}
	}
	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
