#include "description/HasDefensiveLimits.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cHasDefensiveLimits::cHasDefensiveLimits(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cHasDefensiveLimits::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    std::vector<std::string> secureFunctions {"strcpy", "sprintf", "fgets", "snprintf", "sscanf", "strncpy", "strncat"};
    std::string feature = "-1";
    clang::Expr* sink = bof.GetSink();

    if(sink->getStmtClass() == clang::Stmt::StmtClass::CallExprClass) {
        std::string name = llvm::dyn_cast<clang::CallExpr>(sink)->getDirectCallee()->getNameAsString();
        if (std::find(secureFunctions.begin(), secureFunctions.end(), name) != secureFunctions.end())
        {
            feature = "1";
        }
        else {
            feature = "0";
        }
    }

    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
