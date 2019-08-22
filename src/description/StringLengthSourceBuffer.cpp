#include "description/StringLengthSourceBuffer.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ------------------------------------------------------------------------
cStringLengthSourceBuffer::cStringLengthSourceBuffer(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cStringLengthSourceBuffer::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);

    unsigned counter = 0;
    clang::DeclRefExpr* srcBuffer = bof.GetBuffer(BufferType::SRC);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    if (srcBuffer) {
        for (clang::Expr* sanitizationExpr: bof.GetSinkSanitizations()) {
            if (sanitizationExpr->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sanitizationExpr);
                std::vector<clang::Expr*> potentialStrlenExprs = exprUtils->getFromComparisonBinaryOperator(condBinaryOperator, clang::Stmt::StmtClass::CallExprClass);

                for (clang::Expr* potentialStrlenExpr: potentialStrlenExprs) {
                    clang::CallExpr* potentialStrlenCallExpr = llvm::dyn_cast_or_null<clang::CallExpr>(potentialStrlenExpr);
                    std::string functionName = potentialStrlenCallExpr->getDirectCallee()->getNameAsString();
                    
                    if (functionName == "strlen"){
                        clang::DeclRefExpr* argDeclRefExpr = llvm::dyn_cast<clang::DeclRefExpr>(potentialStrlenCallExpr->getArg(0)->IgnoreCasts());

                        if (argDeclRefExpr->getDecl() == srcBuffer->getDecl()) {
                            counter++;
                            break;
                        }
                    }   
                }
            }
        }
    }

    return decoratedFeature.append(std::to_string(counter)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
