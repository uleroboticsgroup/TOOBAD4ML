#include "description/AddressType.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cAddressType::cAddressType(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cAddressType::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    std::string feature = "-1";
    clang::Expr* sink = bof.GetSink();

    if(sink->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
        clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sink);

        if (condBinaryOperator->getLHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass) {
            bool isDeepBinaryOperator = false;
            clang::Expr* bufferExpr = llvm::dyn_cast_or_null<clang::UnaryOperator>(condBinaryOperator->getLHS()->IgnoreCasts())->getSubExpr()->IgnoreCasts()->IgnoreParens();

            switch(bufferExpr->getStmtClass()) {
                case clang::Stmt::StmtClass::DeclRefExprClass: // *(buffer)
                    feature = "0";
                break;
                case clang::Stmt::StmtClass::BinaryOperatorClass: { // *(buffer + ?) , *(buffer - ?) ...
                    clang::BinaryOperator* indexBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(bufferExpr);

                    do {
                        isDeepBinaryOperator = false;
                        std::string operation = clang::BinaryOperator::getOpcodeStr(indexBinaryOperator->getOpcode()).str();
                        clang::Stmt::StmtClass leftStmtClass = indexBinaryOperator->getLHS()->IgnoreCasts()->IgnoreParens()->getStmtClass();
                        clang::Stmt::StmtClass rightStmtClass = indexBinaryOperator->getRHS()->IgnoreCasts()->IgnoreParens()->getStmtClass();

                        if (leftStmtClass == clang::Stmt::StmtClass::IntegerLiteralClass || 
                            rightStmtClass == clang::Stmt::StmtClass::IntegerLiteralClass) {
                                if (operation == "+" || operation == "-") {
                                    feature = "1"; // *(buffer + 8) , *(buffer - 8)
                                }
                                else if (operation == "*" || operation == "/" || operation == "<<" || operation == ">>") {
                                    feature = "2"; // *(buffer + 2 * 8), *(buffer + 27 / 8)
                                }
                                else if (operation == "%") {
                                    feature = "3";
                                }
                        }
                        else if (leftStmtClass == clang::Stmt::StmtClass::CallExprClass || 
                                rightStmtClass == clang::Stmt::StmtClass::CallExprClass) { // *(buffer + function())
                            
                            clang::Expr* indexCallExpr = leftStmtClass == clang::Stmt::StmtClass::CallExprClass ? indexBinaryOperator->getLHS()->IgnoreCasts()->IgnoreParens() : indexBinaryOperator->getRHS()->IgnoreCasts()->IgnoreParens();

                            feature = "4";
                            clang::CallExpr* callExpr = llvm::dyn_cast<clang::CallExpr>(indexCallExpr);
                            std::string name = callExpr->getDirectCallee()->getNameAsString();
                            
                            if (name == "pow" || name == "sqrt") {
                                feature = "3";
                            }

                        }
                        else if (leftStmtClass == clang::Stmt::StmtClass::ArraySubscriptExprClass || 
                                rightStmtClass == clang::Stmt::StmtClass::ArraySubscriptExprClass) { // *(buffer + buffer2[?]) 
                            
                            feature = "5";
                        }
                        else if(leftStmtClass == clang::Stmt::StmtClass::BinaryOperatorClass || 
                                rightStmtClass == clang::Stmt::StmtClass::BinaryOperatorClass) {

                            indexBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(leftStmtClass == clang::Stmt::StmtClass::BinaryOperatorClass ? indexBinaryOperator->getLHS()->IgnoreCasts()->IgnoreParens() : indexBinaryOperator->getRHS()->IgnoreCasts()->IgnoreParens());
                            isDeepBinaryOperator = true;
                        }
                    } while(isDeepBinaryOperator);

                }
                break;
                case clang::Stmt::StmtClass::CallExprClass: // *(getAddress(?))
                    feature = "4";
                    break;
                case clang::Stmt::StmtClass::ArraySubscriptExprClass: // *(buffer2[?])
                    feature = "5";
                    break;
            }
        }
    }

    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
