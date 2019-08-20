#include "description/SizeDestinationBufferMinusX.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
#include "iostream"
using namespace TOOBAD4ML;
using namespace description;

cSizeDestinationBufferMinusX::cSizeDestinationBufferMinusX(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

std::string cSizeDestinationBufferMinusX::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    unsigned counter = 0;
    clang::DeclRefExpr* dstBuffer = bof.GetBuffer(BufferType::DST);
    
    if (dstBuffer) {
        for (clang::Expr* sanitizationExpr: bof.GetSinkSanitizations()) {
            if (sanitizationExpr->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sanitizationExpr);
                std::vector<clang::Expr*> sideBinaryOperators = exprUtils->getFromComparisonBinaryOperator(condBinaryOperator,clang::Stmt::StmtClass::BinaryOperatorClass);

                for (clang::Expr* sideBinaryOperator: sideBinaryOperators) {
                    clang::BinaryOperator* binaryOperator = llvm::dyn_cast_or_null<clang::BinaryOperator>(sideBinaryOperator);

                    std::vector<clang::Expr*> potentialSizeOfs = exprUtils->getFromComparisonBinaryOperator(binaryOperator, clang::Stmt::StmtClass::UnaryExprOrTypeTraitExprClass);

                    std::vector<clang::Expr*> modifiers = exprUtils->getFromComparisonBinaryOperator(binaryOperator, clang::Stmt::StmtClass::IntegerLiteralClass);
    
                    if (potentialSizeOfs.size() == 1 && modifiers.size() == 1 && clang::BinaryOperator::getOpcodeStr(binaryOperator->getOpcode()).str() == "-") {
                        // Check if the side is 'sizeof(dstBuffer) - 1'
                        clang::UnaryExprOrTypeTraitExpr* potentialSizeOf = llvm::dyn_cast<clang::UnaryExprOrTypeTraitExpr>(potentialSizeOfs[0]);
                        clang::IntegerLiteral* modifier = llvm::dyn_cast<clang::IntegerLiteral>(modifiers[0]);

                        if (potentialSizeOf->getKind() == clang::UnaryExprOrTypeTrait::UETT_SizeOf && exprUtils->getValueFromIntegerLiteral(modifier) > 1) {
                            clang::Expr* unaryExprArg = potentialSizeOf->getArgumentExpr()->IgnoreParens();

                            if (unaryExprArg->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
                                if (exprUtils->getValueFromDeclRefExpr(unaryExprArg) == dstBuffer->getDecl()) {
                                    counter++;
                                    break;
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
