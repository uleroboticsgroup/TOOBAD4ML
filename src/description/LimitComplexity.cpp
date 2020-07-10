#include "description/LimitComplexity.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
#include "iostream"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cLimitComplexity::cLimitComplexity(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cLimitComplexity::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    std::map<std::string, unsigned int> writeCalls = {
        // String copy 
        { "strncpy", 2 },
        // String concatenation 
        { "strncat", 2 },
        // Memory alteration
        { "memcpy", 2 }, { "memmove", 2 },
        // Formatted string output
        { "snprintf", 1 },
        // Unformatted string input
        { "fgets", 1 }
    };

    std::string feature = "-1";
    clang::Expr* sink = bof.GetSink();

    if(sink->getStmtClass() == clang::Stmt::StmtClass::CallExprClass) {
        clang::CallExpr* sinkCallExpr = llvm::dyn_cast<clang::CallExpr>(sink);

        std::map<std::string, unsigned int>::iterator writeCallsIt = writeCalls.find(sinkCallExpr->getDirectCallee()->getName());
        if(writeCallsIt != writeCalls.end()) {
            clang::Expr* indexExpr = sinkCallExpr->getArg(writeCallsIt->second)->IgnoreCasts();
            switch(indexExpr->getStmtClass()) {
                case clang::Stmt::StmtClass::IntegerLiteralClass: // 8
                    feature = "0";
                    break;
                case clang::Stmt::StmtClass::CallExprClass: // function()
                    feature = "4";
                    break;
                case clang::Stmt::StmtClass::DeclRefExprClass: // d
                    feature = "1";
                    break;
                case clang::Stmt::StmtClass::ArraySubscriptExprClass: // buffer2[i]
                    feature = "5";
                    break;
                case clang::Stmt::StmtClass::BinaryOperatorClass: { // ? + ?, ? - ? ...
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
