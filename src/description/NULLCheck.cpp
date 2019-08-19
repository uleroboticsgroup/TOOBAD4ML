#include "description/NULLCheck.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
#include "iostream"
using namespace TOOBAD4ML;
using namespace description;

cNULLCheck::cNULLCheck(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

std::string cNULLCheck::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    unsigned counter = 0;
    int compareValue = -1;
    clang::ValueDecl* bufferValueDecl = nullptr;
    clang::DeclRefExpr* srcBuffer = bof.GetBuffer(BufferType::SRC);

    if (srcBuffer) {
        for (clang::Expr* sanitizationExpr: bof.GetSinkSanitizations()) {

            if (sanitizationExpr->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sanitizationExpr);
                if(!clang::BinaryOperator::isAssignmentOp(condBinaryOperator->getOpcode())) {

                    std::vector<clang::Expr*> sideExprs;
                    sideExprs.push_back(condBinaryOperator->getLHS()->IgnoreCasts());
                    sideExprs.push_back(condBinaryOperator->getRHS()->IgnoreCasts());

                    for (clang::Expr* expr: sideExprs) {
                        bool finish = false;
                        clang::Expr* currentExpr = expr;
                        while(!finish) {
                            switch(currentExpr->getStmtClass()) {
                                case clang::Stmt::StmtClass::UnaryOperatorClass:
                                    currentExpr = exprUtils->getExprFromUnaryOperator(currentExpr);
                                    break;
                                case clang::Stmt::StmtClass::DeclRefExprClass: 
                                    bufferValueDecl = exprUtils->getValueFromDeclRefExpr(currentExpr);
                                    finish = true;
                                    break;
                                
                                case clang::Stmt::StmtClass::IntegerLiteralClass:
                                    compareValue = exprUtils->getValueFromIntegerLiteral(currentExpr);
                                    finish = true;
                                    break;
                                
                                case clang::Stmt::StmtClass::ArraySubscriptExprClass: {
                                    clang::DeclRefExpr* bufferDeclRefExpr = exprUtils->getArrayFromArraySubscriptExpr(currentExpr);
                                    bufferValueDecl = exprUtils->getValueFromDeclRefExpr(bufferDeclRefExpr);
                                    finish = true;
                                    break;
                                }
                                default:
                                    finish = true;
                                    break;
                            }
                        }
                    }

                    if (bufferValueDecl == srcBuffer->getDecl() && compareValue == 0) {
                        counter++;
                    }

                    bufferValueDecl = nullptr;
                    compareValue = -1;
                }
            }
        }
    }

    return decoratedFeature.append(std::to_string(counter)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
