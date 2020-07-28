#include "description/InputDependentPredicates.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
#include "iostream"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cInputDependentPredicates::cInputDependentPredicates(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cInputDependentPredicates::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    int feature = 0;
    
    std::map<std::string, int> sinkTypes = {
    { "strcpy", 0 }, { "strncpy", 0 },
    { "strcat", 0 }, { "strncat", 0 },
    { "memcpy",  0}, { "memmove", 0 },
    { "sprintf", 0 }, { "snprintf", 0 },
    { "gets", 0 }, { "fgets", 0 },
    { "scanf", 1 },{ "sscanf", 0 }};

    cExprUtils* exprUtils = cExprUtils::GetInstance();
    SinkPathGraph spg = cpg.GetSPG(*(bof.GetSink()));

    if (bof.GetBuffer(BufferType::SRC)) {
        for(clang::CFGStmt stmt: spg) {
            clang::Expr* expr = const_cast<clang::Expr*>(llvm::dyn_cast<clang::Expr>(stmt.getStmt()));
            if(expr && exprUtils->isExprInsideExpr(expr, bof.GetBuffer(BufferType::SRC)) && expr != bof.GetSink()){
                feature += 1;
            }
        }
    }

    return decoratedFeature.append(std::to_string(feature)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
