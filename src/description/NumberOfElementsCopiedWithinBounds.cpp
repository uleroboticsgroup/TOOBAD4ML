#include "description/NumberOfElementsCopiedWithinBounds.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Type.h"
#include "description/ExprUtils.h"
#include "iostream"
// ----------------------------------------------------------------------------

using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cNumberOfElementsCopiedWithinBounds::cNumberOfElementsCopiedWithinBounds(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cNumberOfElementsCopiedWithinBounds::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
	std::string feature = "-1";
	cExprUtils* exprUtils = cExprUtils::GetInstance();
	int limit = 0;
	int destinationBufferSize = 0;
	int sourceBufferSize = 0;

	if (bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass && 
		bof.GetBuffer(BufferType::DST) != nullptr // && bof.getSrcBuffer != nullptr
		) {
		
		clang::CallExpr* sinkCallExpr = llvm::dyn_cast<clang::CallExpr>(bof.GetSink());

		if (sinkCallExpr->getDirectCallee()->getNameAsString() == "strncpy" && 
			sinkCallExpr->getNumArgs() == 3) {
			
			destinationBufferSize = exprUtils->guessBufferSize(bof.GetBuffer(BufferType::DST), cpg.GetAST().getASTContext());
			// sourceBufferSize = guessBufferSize(bof.GetSrcBuffer)
			clang::Expr* limitVarExpr = sinkCallExpr->getArg(2)->IgnoreCasts();
			limit = exprUtils->guessArgumentSize(limitVarExpr, cpg.GetAST().getASTContext());
		}
		
		if (destinationBufferSize == -1 || sourceBufferSize == -1 || limit == -1) {
			// Unknown - cannot be evaluated
			feature = "2";
		}
		else if(limit > 0 && limit < destinationBufferSize && limit < sourceBufferSize) {
			// True - within bounds
			feature = "1";
		}
		else {
			// False - outside bounds
			feature = "0";
		}

	}

	return decoratedFeature.append(feature.append(cDescriptorDecorator::FEATURE_SEPARATOR));
}