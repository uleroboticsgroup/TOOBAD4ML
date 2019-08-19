#include "description/SizeSourceBuffer.h"
#include "description/BufferOverflow.h"
using namespace TOOBAD4ML;
using namespace description;

cSizeSourceBuffer::cSizeSourceBuffer(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

std::string cSizeSourceBuffer::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);

    unsigned counter = 0;
    clang::DeclRefExpr* srcBuffer = bof.GetBuffer(BufferType::SRC);
    
    if (srcBuffer) {
        for (clang::Expr* sanitizationExpr: bof.GetSinkSanitizations()) {
            //std::cout << "\n";
            //sanitizationExpr->dumpColor();
            if (sanitizationExpr->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sanitizationExpr);
                
                if(!clang::BinaryOperator::isAssignmentOp(condBinaryOperator->getOpcode())) {
                    clang::UnaryExprOrTypeTraitExpr* potentialStrlenUnaryExpr = nullptr;

                    // Check left side
                    if (condBinaryOperator->getLHS()->getStmtClass() == clang::Stmt::StmtClass::UnaryExprOrTypeTraitExprClass) {
                        potentialStrlenUnaryExpr = llvm::dyn_cast<clang::UnaryExprOrTypeTraitExpr>(condBinaryOperator->getLHS()->IgnoreCasts());
                    }
                    // Check right side
                    else if (condBinaryOperator->getRHS()->getStmtClass() == clang::Stmt::StmtClass::UnaryExprOrTypeTraitExprClass) {
                        potentialStrlenUnaryExpr = llvm::dyn_cast<clang::UnaryExprOrTypeTraitExpr>(condBinaryOperator->getRHS()->IgnoreCasts());
                    }

                    if (potentialStrlenUnaryExpr) {
                        // Check if the function is sizeof(_)
                        if (potentialStrlenUnaryExpr->getKind() == clang::UnaryExprOrTypeTrait::UETT_SizeOf) {
                            clang::Expr* unaryExprArg = potentialStrlenUnaryExpr->getArgumentExpr()->IgnoreParens();

                            if (unaryExprArg->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
                                if (llvm::dyn_cast<clang::DeclRefExpr>(unaryExprArg)->getDecl() == srcBuffer->getDecl()) {
                                    counter++;
                                }
                            }
                        }   
                    }
                }
            }
        }
    }

    return decoratedFeature.append(std::to_string(counter)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
