#include "description/SameSrcDstSize.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cSameSrcDstSize::cSameSrcDstSize(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cSameSrcDstSize::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    std::string feature = "-1";
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    if (bof.GetBuffer(BufferType::DST) && bof.GetBuffer(BufferType::SRC)){
        int dstSize = exprUtils->guessBufferSize(bof.GetBuffer(BufferType::DST), cpg.GetAST().getASTContext());
        int srcSize = exprUtils->guessBufferSize(bof.GetBuffer(BufferType::SRC), cpg.GetAST().getASTContext());

        if(srcSize != -1 && dstSize != -1) {
            if (srcSize == dstSize) {
                feature = "1";
            }
            else {
                feature = "0";
            }
        }

    }

    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
