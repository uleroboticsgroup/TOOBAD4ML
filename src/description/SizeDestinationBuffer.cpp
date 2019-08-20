#include "description/SizeDestinationBuffer.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"

using namespace TOOBAD4ML;
using namespace description;

cSizeDestinationBuffer::cSizeDestinationBuffer(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

std::string cSizeDestinationBuffer::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);

    unsigned counter = 0;
    clang::DeclRefExpr* dstBuffer = bof.GetBuffer(BufferType::DST);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    if (dstBuffer) {
        for (clang::Expr* sanitizationExpr: bof.GetSinkSanitizations()) {
            if (sanitizationExpr->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sanitizationExpr);
                std::vector<clang::Expr*> potentialStrlenUnaryExprs = exprUtils->getFromComparisonBinaryOperator(condBinaryOperator, clang::Stmt::StmtClass::UnaryExprOrTypeTraitExprClass);

                for (clang::Expr* potentialStrlenUnaryExpr: potentialStrlenUnaryExprs) {
                    // Check if the function is sizeof(_)
                    clang::UnaryExprOrTypeTraitExpr* potentialStrlenCastedUnaryExpr = llvm::dyn_cast_or_null<clang::UnaryExprOrTypeTraitExpr>(potentialStrlenUnaryExpr);
                    if (potentialStrlenCastedUnaryExpr->getKind() == clang::UnaryExprOrTypeTrait::UETT_SizeOf) {
                        clang::Expr* unaryExprArg = potentialStrlenCastedUnaryExpr->getArgumentExpr()->IgnoreParens();

                        if (unaryExprArg->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
                            if (exprUtils->getValueFromDeclRefExpr(unaryExprArg) == dstBuffer->getDecl()) {
                                counter++;
                            }
                        }
                    }   
                }
            }
        }
    }

    return decoratedFeature.append(std::to_string(counter)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
