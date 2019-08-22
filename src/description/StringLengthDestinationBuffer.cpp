#include "description/StringLengthDestinationBuffer.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ------------------------------------------------------------------------
cStringLengthDestinationBuffer::cStringLengthDestinationBuffer(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cStringLengthDestinationBuffer::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();
    unsigned counter = 0;
    clang::DeclRefExpr* dstBuffer = bof.GetBuffer(BufferType::DST);
    
    if (dstBuffer) {
        for (clang::Expr* sanitizationExpr: bof.GetSinkSanitizations()) {
            //std::cout << "\n";
            //sanitizationExpr->dumpColor();
            if (sanitizationExpr->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sanitizationExpr);
                std::vector<clang::Expr*> potentialStrlenExprs = exprUtils->getFromComparisonBinaryOperator(condBinaryOperator, clang::Stmt::StmtClass::CallExprClass);
                
                for (clang::Expr* potentialStrlenExpr: potentialStrlenExprs) {
                    clang::CallExpr* potentialStrlenCallExpr = llvm::dyn_cast<clang::CallExpr>(potentialStrlenExpr);
                    std::string functionName = potentialStrlenCallExpr->getDirectCallee()->getNameAsString();
                    
                    if (functionName == "strlen"){
                        clang::DeclRefExpr* argDeclRefExpr = llvm::dyn_cast<clang::DeclRefExpr>(potentialStrlenCallExpr->getArg(0)->IgnoreCasts());

                        if (argDeclRefExpr->getDecl() == dstBuffer->getDecl()) {
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
