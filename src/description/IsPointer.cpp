#include "description/IsPointer.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR & DESTRUCTORS
// ------------------------------------------------------------------------
cIsPointer::cIsPointer(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cIsPointer::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    std::string feature = "0";
    clang::DeclRefExpr* dstBuffer = bof.GetBuffer(BufferType::DST);

    if (dstBuffer) {
        if (dstBuffer->getDecl()->getType().getTypePtr()->isPointerType()) {
            feature = "1";
        }
    }

    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}