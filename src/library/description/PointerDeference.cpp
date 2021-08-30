#include "description/PointerDeference.h"
#include "description/BufferOverflow.h"

using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cPointerDeference::cPointerDeference(IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};


// INHERITED METHODS
// ----------------------------------------------------------------------------

bool Traverse(clang::Expr* expr){
	if (expr->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
        clang::BinaryOperator* bo = llvm::dyn_cast_or_null<clang::BinaryOperator>(expr->IgnoreCasts());
        if (Traverse(bo->getLHS()->IgnoreCasts())) {
            return true;
        }

        if (Traverse(bo->getRHS()->IgnoreCasts())) {
            return true;
        }
    }
    else if (expr->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass){
        clang::CallExpr* call = llvm::dyn_cast_or_null<clang::CallExpr>(expr->IgnoreCasts());        
        for(int index = call->getNumArgs() - 1; index >= 0; index--){
            if (Traverse(call->getArg(index))) {
                return true;
            }
        }
    }
    else if (expr->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::ArraySubscriptExprClass){
        return true;
    }
    else if (expr->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass) {
        std::string operation = clang::UnaryOperator::getOpcodeStr(llvm::dyn_cast_or_null<clang::UnaryOperator>(expr->IgnoreCasts())->getOpcode()).str();

        if (operation == "*") {
            return true;
        }
    }

    return false;
}

std::string cPointerDeference::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
			cDescriptorDecorator::ExtractFeature(cpg, bof);

	std::string feature = "0";
	
    if (Traverse(bof.GetSink())) {
        feature = "1";
    }

	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}