#include "description/StringLengthSourceBuffer.h"
#include "description/BufferOverflow.h"

using namespace TOOBAD4ML;
using namespace description;

cStringLengthSourceBuffer::cStringLengthSourceBuffer(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

std::string cStringLengthSourceBuffer::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);

    unsigned counter = 0;
    clang::DeclRefExpr* srcBuffer = bof.GetBuffer(BufferType::SRC);
    
    if (srcBuffer) {
        for (clang::Expr* sanitizationExpr: bof.GetSinkSanitizations()) {
            //std::cout << "\n";
            //sanitizationExpr->dumpColor();
            if (sanitizationExpr->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sanitizationExpr);

                clang::CallExpr* potentialStrlenCallExpr = nullptr;

                if (condBinaryOperator->getLHS()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass) {
                    potentialStrlenCallExpr = llvm::dyn_cast<clang::CallExpr>(condBinaryOperator->getLHS()->IgnoreCasts());
                }
                else if (condBinaryOperator->getRHS()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass) {
                    potentialStrlenCallExpr = llvm::dyn_cast<clang::CallExpr>(condBinaryOperator->getRHS()->IgnoreCasts());
                }

                if (potentialStrlenCallExpr) {
                    std::string functionName = potentialStrlenCallExpr->getDirectCallee()->getNameAsString();

                    //std::cout << functionName << "\n";
                    //potentialStrlenCallExpr->getArg(0)->dumpColor();
                    if (functionName == "strlen"){
                        clang::DeclRefExpr* argDeclRefExpr = llvm::dyn_cast<clang::DeclRefExpr>(potentialStrlenCallExpr->getArg(0)->IgnoreCasts());

                        if (argDeclRefExpr->getDecl() == srcBuffer->getDecl()) {
                            counter++;
                        }
                    }   
                }
        
            }
        }
    }

    return decoratedFeature.append(std::to_string(counter)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
