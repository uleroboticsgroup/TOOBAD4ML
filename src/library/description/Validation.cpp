#include "description/Validation.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
#include "iostream"
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cValidation::cValidation(IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};


std::string cValidation::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
			cDescriptorDecorator::ExtractFeature(cpg, bof);

	int feature = 0;

	cExprUtils* exprUtils = cExprUtils::GetInstance();
    clang::DeclRefExpr* dstBuffer = bof.GetBuffer(BufferType::DST);
    std::vector<clang::Expr*> validations = bof.GetSinkSanitizations();
	
    if(bof.GetBuffer(BufferType::DST)) {
		for (clang::Expr* currentValidator: validations) {
            if(exprUtils->isExprInsideExpr(currentValidator, dstBuffer) && currentValidator != bof.GetSink()){
                feature += 1;
            }
        }   
	}

	return decoratedFeature.append(std::to_string(feature)).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}