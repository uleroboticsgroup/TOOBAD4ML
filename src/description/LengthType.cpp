#include "description/LengthType.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cLengthType::cLengthType(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};
// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cLengthType::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    std::string feature = "-1";
    bool isDeepBinaryOperator = false;
    clang::Expr* sink = bof.GetSink();

    if(sink->getStmtClass() == clang::Stmt::StmtClass::CallExprClass) {
        clang::CallExpr* sinkCallExpr = llvm::dyn_cast<clang::CallExpr>(sink);

        if (sinkCallExpr->getDirectCallee()->getNameAsString() == "memcpy") {
            clang::Expr* sizeExpr = sinkCallExpr->getArg(2)->IgnoreCasts();

            switch(sizeExpr->getStmtClass()) {
                case clang::Stmt::StmtClass::IntegerLiteralClass: //  memcpy(buffer, buffer2, 8)
                    feature = "0";
                    break;
                case clang::Stmt::StmtClass::CallExprClass:{ // memcpy(buffer, buffer2, foo())
                    feature = "4";
                    clang::CallExpr* callExpr = llvm::dyn_cast<clang::CallExpr>(sizeExpr);
                    std::string name = callExpr->getDirectCallee()->getNameAsString();
                    
                    if (name == "pow" || name == "sqrt") {
                        feature = "3";
                    }
                }
                break;
                case clang::Stmt::StmtClass::BinaryOperatorClass: { // memcpy(buffer, buffer2, ? + ?) ...
                    clang::BinaryOperator* sizeBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sizeExpr);

                    do {
                        isDeepBinaryOperator = false;
                        std::string operation = clang::BinaryOperator::getOpcodeStr(sizeBinaryOperator->getOpcode()).str();

                        clang::Stmt::StmtClass leftStmtClass = sizeBinaryOperator->getLHS()->IgnoreCasts()->getStmtClass();
                        clang::Stmt::StmtClass rightStmtClass = sizeBinaryOperator->getRHS()->IgnoreCasts()->getStmtClass();

                        if (!(leftStmtClass == clang::Stmt::StmtClass::BinaryOperatorClass || 
                            rightStmtClass == clang::Stmt::StmtClass::BinaryOperatorClass)) {

                            if (operation == "+" || operation == "-") {
                                feature = "1";
                            }
                            else if(operation == "*" || operation == "/" || operation == "<<" || operation == ">>") {
                                feature = "2";
                            }
                            else if(operation == "%") {
                                feature = "3";
                            }
                        }
                        else {

                            sizeBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(leftStmtClass == clang::Stmt::StmtClass::BinaryOperatorClass ? sizeBinaryOperator->getLHS()->IgnoreCasts() : sizeBinaryOperator->getRHS()->IgnoreCasts());
                            isDeepBinaryOperator = true;
                        }
                    } while(isDeepBinaryOperator);
                }
                break;
                case clang::Stmt::StmtClass::ArraySubscriptExprClass: // memcpy(buffer, buffer2, buffer[3])
                    feature = "5";
                break;
            }
        }
    }

    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
