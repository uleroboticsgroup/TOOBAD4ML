#include "description/ContainerType.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cContainerType::cContainerType(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cContainerType::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    std::string feature = "-1";
    clang::Expr* sink = bof.GetSink();

    if(sink->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
        clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sink);
        clang::Expr* bufferExpr = nullptr;
        
        switch (condBinaryOperator->getLHS()->IgnoreCasts()->getStmtClass()) {
            case clang::Stmt::StmtClass::ArraySubscriptExprClass: {
                bufferExpr = llvm::dyn_cast_or_null<clang::ArraySubscriptExpr>(condBinaryOperator->getLHS()->IgnoreCasts())->getLHS()->IgnoreCasts()->IgnoreParens();
            }
            break;
            case clang::Stmt::StmtClass::CallExprClass: {
                std::map<std::string, int> sinkTypes = {
                    { "strcpy", 0, }, { "strncpy", 0 },
                    { "strcat", 0 }, { "strncat", 0 },
                    { "memcpy", 0 }, { "memmove", 0 },
                    { "sprintf", 0 }, { "snprintf", 0 },
                    { "gets", 0 }, { "fgets", 0 },
                    { "scanf", 1 },{ "sscanf", 0 }, };

                clang::CallExpr* sinkCallExpr = llvm::dyn_cast_or_null<clang::CallExpr>(condBinaryOperator->getLHS()->IgnoreCasts());
                bufferExpr = sinkCallExpr->getArg(sinkTypes[sinkCallExpr->getDirectCallee()->getNameAsString()])->IgnoreCasts()->IgnoreParens();
            }
            break;
        }

        if (bufferExpr) {
            switch(bufferExpr->getStmtClass())  {
                case clang::Stmt::StmtClass::DeclRefExprClass:
                    feature = "0";
                    break;
                case clang::Stmt::StmtClass::ArraySubscriptExprClass:
                    feature = "1";
                    break;
                case clang::Stmt::StmtClass::MemberExprClass:
                    feature = "2";
                    break;
                default:
                    feature = "3";
                    break;
            }
        }

    }

    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
