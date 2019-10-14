#include "description/IsSourceABuffer.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR & DESTRUCTORS
// ------------------------------------------------------------------------
cIsSourceABuffer::cIsSourceABuffer(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cIsSourceABuffer::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    std::string feature = "0";
    clang::DeclRefExpr* srcBuffer = bof.GetBuffer(BufferType::SRC);

    if (srcBuffer) {
        if (srcBuffer->getDecl()->getType().getTypePtr()->isArrayType()) {
            feature = "1";
        }
    }

    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}