#include "description/ViolatedBound.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
#include "description/CodePropertyGraph.h"
using namespace TOOBAD4ML;
using namespace description;
#include "iostream"
// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cViolatedBound::cViolatedBound(IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cViolatedBound::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
			cDescriptorDecorator::ExtractFeature(cpg, bof);

    cExprUtils* utils = cExprUtils::GetInstance();
	std::string feature = "-1";
	
	if (bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
        clang::BinaryOperator* bo = llvm::dyn_cast_or_null<clang::BinaryOperator>(bof.GetSink()->IgnoreCasts());

        if (bo->getLHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::ArraySubscriptExprClass){
            clang::ArraySubscriptExpr* dstBuffer = llvm::dyn_cast<clang::ArraySubscriptExpr>(bo->getLHS()->IgnoreCasts());
            
            clang::Expr* arrayValue = utils->getIndexFromArraySubscriptExpr(dstBuffer);

            if (arrayValue->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass) {
                if("-" == clang::UnaryOperator::getOpcodeStr(llvm::dyn_cast_or_null<clang::UnaryOperator>(arrayValue)->getOpcode()).str()) {
                    feature = "0";
                }
            }
            else if (arrayValue->getStmtClass() == clang::Stmt::StmtClass::IntegerLiteralClass) {
                int value = utils->getValueFromIntegerLiteral(arrayValue);
               
                if (utils->guessBufferSize(bof.GetBuffer(BufferType::DST), cpg.GetAST().getASTContext()) <= value) {
                    feature = "1";
                }
            }
        }
    }
	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
