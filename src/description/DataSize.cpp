#include "description/DataSize.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
#include "description/CodePropertyGraph.h"
#include "iostream"
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cDataSize::cDataSize(IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cDataSize::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
			cDescriptorDecorator::ExtractFeature(cpg, bof);

    cExprUtils* utils = cExprUtils::GetInstance();
	std::string feature = "0";

	clang::DeclRefExpr* dstBuffer = bof.GetBuffer(BufferType::DST);
    if(dstBuffer) {
        int baseSize = utils->guessBufferSize(bof.GetBuffer(BufferType::DST), cpg.GetAST().getASTContext());

        if (bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
            clang::BinaryOperator* bo = llvm::dyn_cast_or_null<clang::BinaryOperator>(bof.GetSink()->IgnoreCasts());

            if (bo->getLHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::ArraySubscriptExprClass){
                clang::ArraySubscriptExpr* dstBuffer = llvm::dyn_cast<clang::ArraySubscriptExpr>(bo->getLHS()->IgnoreCasts());
                
                clang::Expr* arrayValue = utils->getIndexFromArraySubscriptExpr(dstBuffer);
                if (arrayValue->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass) {
                    clang::UnaryOperator* innerExpr = llvm::dyn_cast<clang::UnaryOperator>(arrayValue);

                    if (innerExpr->getSubExpr()->getStmtClass() == clang::Stmt::StmtClass::IntegerLiteralClass) {
                        int value = utils->getValueFromIntegerLiteral(innerExpr->getSubExpr());

                        if("-" == clang::UnaryOperator::getOpcodeStr(llvm::dyn_cast_or_null<clang::UnaryOperator>(arrayValue)->getOpcode()).str()) {
                            feature = std::to_string(-value);
                        }

                    }
                }
                else if (arrayValue->getStmtClass() == clang::Stmt::StmtClass::IntegerLiteralClass) {
                    int value = utils->getValueFromIntegerLiteral(arrayValue);
                    feature = std::to_string(value - baseSize);
                }
                else if (arrayValue->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                    int total = utils->getTotalOfBinaryOperator(arrayValue->IgnoreCasts()->IgnoreParens());
                    feature = std::to_string(total - baseSize);
                }
                else if(arrayValue->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
                    clang::ValueDecl* vd = llvm::dyn_cast<clang::DeclRefExpr>(arrayValue->IgnoreCasts())->getDecl();

                    if(vd->getKind() == clang::Decl::Kind::Var) {
                        const clang::Expr* innerinnerExpr = llvm::dyn_cast<clang::VarDecl>(vd)->getAnyInitializer();

                        int value = llvm::dyn_cast_or_null<clang::IntegerLiteral>(innerinnerExpr)->getValue().getLimitedValue();
                        feature = std::to_string(value - baseSize);
                    }
                }

            }
            else if (bo->getLHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass) {
                if("*" == clang::UnaryOperator::getOpcodeStr(llvm::dyn_cast_or_null<clang::UnaryOperator>(bo->getLHS()->IgnoreCasts())->getOpcode()).str()) {
                    clang::Expr* innerExpr = llvm::dyn_cast_or_null<clang::UnaryOperator>(bo->getLHS()->IgnoreCasts()->IgnoreParens())->getSubExpr();
                    if (innerExpr->IgnoreCasts()->IgnoreParens()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                        int total = utils->getTotalOfBinaryOperator(innerExpr->IgnoreCasts()->IgnoreParens());

                        feature == std::to_string(total - baseSize);

                    }
                }
            }
        }
    }

	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
