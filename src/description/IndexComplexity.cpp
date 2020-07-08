#include "description/IndexComplexity.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cIndexComplexity::cIndexComplexity(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cIndexComplexity::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    std::string feature = "-1";
    clang::Expr* sink = bof.GetSink();

    if(sink->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
        clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sink);

        if (condBinaryOperator->getLHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::ArraySubscriptExprClass) {
            bool isDeepBinaryOperator = false;
            clang::Expr* indexExpr = exprUtils->getIndexFromArraySubscriptExpr(condBinaryOperator->getLHS()->IgnoreCasts())->IgnoreCasts();
            clang::Expr* bufferExpr = llvm::dyn_cast_or_null<clang::ArraySubscriptExpr>(condBinaryOperator->getLHS()->IgnoreCasts())->getLHS()->IgnoreCasts()->IgnoreParens();
            
            // The brackets
            switch(indexExpr->getStmtClass()) {
                case clang::Stmt::StmtClass::IntegerLiteralClass: // buffer[8]
                    feature = "0";
                    break;
                case clang::Stmt::StmtClass::CallExprClass: // buffer[function()]
                    feature = "4";
                    break;
                case clang::Stmt::StmtClass::DeclRefExprClass: // buffer[d]
                    feature = "1";
                    break;
                case clang::Stmt::StmtClass::ArraySubscriptExprClass: // buffer[buffer2[i]]
                    feature = "5";
                    break;
                case clang::Stmt::StmtClass::BinaryOperatorClass: { // buffer[? + ?], buffer[? - ?] ...
                    clang::BinaryOperator* bopIndex = llvm::dyn_cast<clang::BinaryOperator>(indexExpr);
                    bool check = true;

                    while(check){
                        check = false;
                        clang::Expr* leftPart = bopIndex->getLHS()->IgnoreCasts()->IgnoreParens();
                        clang::Expr* rightPart = bopIndex->getRHS()->IgnoreCasts()->IgnoreParens();

                        if(leftPart->getStmtClass() == clang::Stmt::StmtClass::CallExprClass){
                            if(llvm::dyn_cast<clang::CallExpr>(leftPart)->getDirectCallee()->getName() == "pow" || 
                            llvm::dyn_cast<clang::CallExpr>(leftPart)->getDirectCallee()->getName() == "sqrt"){
                                    feature = "3";
                            }
                        }
                        else if(rightPart->getStmtClass() == clang::Stmt::StmtClass::CallExprClass){
                            if(llvm::dyn_cast<clang::CallExpr>(rightPart)->getDirectCallee()->getName() == "pow" || 
                            llvm::dyn_cast<clang::CallExpr>(rightPart)->getDirectCallee()->getName() == "sqrt"){
                                    feature = "3";
                            }
                        }
                        else{
                            if (leftPart->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass){
                                bopIndex = llvm::dyn_cast<clang::BinaryOperator>(leftPart);
                                check = true;
                            }
                            else if (rightPart->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass){
                                bopIndex = llvm::dyn_cast<clang::BinaryOperator>(rightPart);
                                check = true;
                            }
                            else {
                                feature = "2";
                            }
                        }
                    }
                }
            }
        }
    }



    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
