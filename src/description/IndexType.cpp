#include "description/IndexType.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cIndexType::cIndexType(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

std::string analyzeCallExpr(clang::Expr* expr) {
    std::string feature = "4";
    clang::CallExpr* callExpr = llvm::dyn_cast<clang::CallExpr>(expr);
    std::string name = callExpr->getDirectCallee()->getNameAsString();
    
    if (name == "pow" || name == "sqrt") {
        feature = "3";
    }

    return feature;
}

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cIndexType::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    std::string feature = "-1";
    std::string featureIndex = "-1";
    std::string featureArray = "-1";
    clang::Expr* sink = bof.GetSink();

    // ? JUST [i] ?

    if(sink->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
        bool isDeepBinaryOperator = false;
        clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sink);
        clang::Expr* indexExpr = exprUtils->getIndexFromArraySubscriptExpr(condBinaryOperator->getLHS()->IgnoreCasts())->IgnoreCasts();
        clang::Expr* bufferExpr = llvm::dyn_cast_or_null<clang::ArraySubscriptExpr>(condBinaryOperator->getLHS()->IgnoreCasts())->getLHS()->IgnoreCasts()->IgnoreParens();
        
        // The brackets
        switch(indexExpr->getStmtClass()) {
            case clang::Stmt::StmtClass::IntegerLiteralClass: // buffer[8]
                featureIndex = "0";
                break;
            case clang::Stmt::StmtClass::CallExprClass: // buffer[function()]
                featureIndex = analyzeCallExpr(indexExpr);
                break;
            case clang::Stmt::StmtClass::BinaryOperatorClass: { // buffer[? + ?], buffer[? - ?] ...
                clang::BinaryOperator* indexBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(indexExpr);

                do {
                    isDeepBinaryOperator = false;
                    std::string operation = clang::BinaryOperator::getOpcodeStr(indexBinaryOperator->getOpcode()).str();

                    clang::Stmt::StmtClass leftStmtClass = indexBinaryOperator->getLHS()->IgnoreCasts()->getStmtClass();
                    clang::Stmt::StmtClass rightStmtClass = indexBinaryOperator->getRHS()->IgnoreCasts()->getStmtClass();

                    if (!(leftStmtClass == clang::Stmt::StmtClass::BinaryOperatorClass || 
                        rightStmtClass == clang::Stmt::StmtClass::BinaryOperatorClass)) {

                        if (operation == "+" || operation == "-") {
                            featureIndex = "1";
                        }
                        else if(operation == "*" || operation == "/" || operation == "<<" || operation == ">>") {
                            featureIndex = "2";
                        }
                        else if(operation == "%") {
                            featureIndex = "3";
                        }
                    }
                    else {

                        indexBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(leftStmtClass == clang::Stmt::StmtClass::BinaryOperatorClass ? indexBinaryOperator->getLHS()->IgnoreCasts() : indexBinaryOperator->getRHS()->IgnoreCasts());
                        isDeepBinaryOperator = true;
                    }
                }while(isDeepBinaryOperator);
            }
            break;
            case clang::Stmt::StmtClass::ArraySubscriptExprClass: // buffer[buffer2[8]]
                featureIndex = "6";

        }

        // The variable of the buffer itself
        switch(bufferExpr->getStmtClass()) {
            case clang::Stmt::StmtClass::BinaryOperatorClass: { // (buffer + ?) [?], (buffer - ?) [?] ...
                clang::BinaryOperator* indexBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(bufferExpr);

                do {
                    isDeepBinaryOperator = false;
                    std::string operation = clang::BinaryOperator::getOpcodeStr(indexBinaryOperator->getOpcode()).str();

                    clang::Stmt::StmtClass leftStmtClass = indexBinaryOperator->getLHS()->IgnoreCasts()->getStmtClass();
                    clang::Stmt::StmtClass rightStmtClass = indexBinaryOperator->getRHS()->IgnoreCasts()->getStmtClass();

                    if (leftStmtClass == clang::Stmt::StmtClass::IntegerLiteralClass || 
                        rightStmtClass == clang::Stmt::StmtClass::IntegerLiteralClass) {

                            if (operation == "+" || operation == "-") {
                                featureArray = "1"; // (buffer + 8) [?], (buffer - 8) [?]
                            }
                            else if (operation == "*" || operation == "/") {
                                featureArray = "2"; // (buffer * 8) [?], (buffer / 8) [?]
                            }
                    }
                    else if (leftStmtClass == clang::Stmt::StmtClass::CallExprClass || 
                            rightStmtClass == clang::Stmt::StmtClass::CallExprClass) { // (buffer + function()) [?]
                        
                        clang::Expr* indexCallExpr = leftStmtClass == clang::Stmt::StmtClass::CallExprClass ? indexBinaryOperator->getLHS()->IgnoreCasts() : indexBinaryOperator->getRHS()->IgnoreCasts();

                        featureArray = analyzeCallExpr(indexCallExpr);

                    }
                    else if (leftStmtClass == clang::Stmt::StmtClass::ArraySubscriptExprClass || 
                            rightStmtClass == clang::Stmt::StmtClass::ArraySubscriptExprClass) { // (buffer + buffer2[?]) [?]
                        
                        featureArray = "6";
                    }
                    else if(leftStmtClass == clang::Stmt::StmtClass::BinaryOperatorClass || 
                            rightStmtClass == clang::Stmt::StmtClass::BinaryOperatorClass) {

                        indexBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(leftStmtClass == clang::Stmt::StmtClass::BinaryOperatorClass ? indexBinaryOperator->getLHS()->IgnoreCasts() : indexBinaryOperator->getRHS()->IgnoreCasts());
                        isDeepBinaryOperator = true;
                    }
                } while(isDeepBinaryOperator);

            }
            break;
            case clang::Stmt::StmtClass::CallExprClass: // (getAddress(?)) [?]
                featureArray = "4";
                break;
            case clang::Stmt::StmtClass::ArraySubscriptExprClass: // (buffer2[?]) [?]
                featureArray = "5";
                break;
        }

        if (featureArray == "-1") {
            feature = featureIndex;
        }
        else {
            feature = featureArray;
        }
    }

    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
