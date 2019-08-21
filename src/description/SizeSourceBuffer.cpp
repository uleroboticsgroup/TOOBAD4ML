#include "description/SizeSourceBuffer.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
#include "iostream"
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
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    if (srcBuffer) {
        for (clang::Expr* sanitizationExpr: bof.GetSinkSanitizations()) {
            //std::cout << "\n";
            if (sanitizationExpr->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sanitizationExpr);
                
                std::vector<clang::Expr*> potentialStrlenUnaryExprs = exprUtils->getFromComparisonBinaryOperator(condBinaryOperator, clang::Stmt::StmtClass::UnaryExprOrTypeTraitExprClass);

                for (clang::Expr* potentialStrlenUnaryExpr: potentialStrlenUnaryExprs) {
                    clang::UnaryExprOrTypeTraitExpr* potentialStrlenCastedUnaryExpr = llvm::dyn_cast_or_null<clang::UnaryExprOrTypeTraitExpr>(potentialStrlenUnaryExpr);
                    // Check if the function is sizeof(srcBuffer)
                    if (potentialStrlenCastedUnaryExpr->getKind() == clang::UnaryExprOrTypeTrait::UETT_SizeOf) {
                        clang::Expr* unaryExprArg = potentialStrlenCastedUnaryExpr->getArgumentExpr()->IgnoreParens();

                        if (unaryExprArg->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
                            if (exprUtils->getValueFromDeclRefExpr(unaryExprArg) == srcBuffer->getDecl()) {
                                counter++;
                                break;
                            }
                        }
                    }   
                }
            }
        }
    }

    return decoratedFeature.append(std::to_string(counter)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
