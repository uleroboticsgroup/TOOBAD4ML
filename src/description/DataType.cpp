#include "description/DataType.h"
#include "description/BufferOverflow.h"

using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cDataType::cDataType(IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};


std::string cDataType::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
			cDescriptorDecorator::ExtractFeature(cpg, bof);

	std::string feature = "-1";
	
    clang::DeclRefExpr* dstBuffer = bof.GetBuffer(BufferType::DST);
    if (dstBuffer->getDecl()->getType().getTypePtr()->isArrayType()){
        const clang::ArrayType* dstBufferArray = llvm::dyn_cast<clang::ArrayType>(dstBuffer->getDecl()->getType());
        const clang::Type* dstBufferType = dstBufferArray->getElementType().getTypePtr();
        
        if(dstBufferType->isCharType()){
            feature = "0";
        }
        else if (dstBufferType->isIntegerType()){
            feature = "1";
        }
        else if (dstBufferType->isFloatingType()) {
            feature = "2";
        }
        else if (dstBufferType->isWideCharType()) {
            feature = "3";
        }
        else if (dstBufferType->isPointerType()) {
            feature = "4";
        }
        else if(dstBufferType->isUnsignedIntegerType()){
            feature = "5";
        }
    }
	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}