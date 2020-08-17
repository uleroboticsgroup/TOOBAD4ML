#include "description/SourceNullTerminated.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cSourceNullTerminated::cSourceNullTerminated(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cSourceNullTerminated::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    std::string feature = "0";
    bool isSourceBuffer = false;
    bool isLastItem = false;
    bool isNullAssignment = false;

    cExprUtils* exprUtils = cExprUtils::GetInstance();
    SinkPathGraph spg = cpg.GetSPG(*(bof.GetSink()));
    clang::DeclRefExpr* srcBuffer = bof.GetBuffer(BufferType::SRC);

    if(srcBuffer){
        for(clang::CFGStmt cfgStmt: spg) {
    		clang::Stmt* stmt = const_cast<clang::Stmt*>(cfgStmt.getStmt());
            if(stmt->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* bop = llvm::dyn_cast<clang::BinaryOperator>(stmt);

                if (bop->getLHS()->IgnoreCasts()->IgnoreParens()->getStmtClass() == clang::Stmt::StmtClass::ArraySubscriptExprClass) {
                    clang::ArraySubscriptExpr* arraySubscript = llvm::dyn_cast<clang::ArraySubscriptExpr>(bop->getLHS()->IgnoreCasts()->IgnoreParens());
                    if (arraySubscript->getLHS()->IgnoreCasts()->IgnoreParens()->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
                        clang::DeclRefExpr* possibleSourceBuffer = llvm::dyn_cast<clang::DeclRefExpr>(arraySubscript->getLHS()->IgnoreCasts()->IgnoreParens());

                        if(possibleSourceBuffer->getDecl() == bof.GetBuffer(BufferType::SRC)->getDecl()) {
                            isSourceBuffer = true;
                        }
                    }
                    
                    if (arraySubscript->getRHS()->IgnoreCasts()->IgnoreParens()->getStmtClass() == clang::Stmt::StmtClass::IntegerLiteralClass) {
                        int bufferSize = exprUtils->guessBufferSize(bof.GetBuffer(BufferType::SRC), cpg.GetAST().getASTContext());
                        int index = llvm::dyn_cast_or_null<clang::IntegerLiteral>(arraySubscript->getRHS()->IgnoreCasts()->IgnoreParens())->getValue().getLimitedValue();

                        if (index == bufferSize - 1) {
                            isLastItem = true;
                        }
                    }
                }

                if (bop->getRHS()->IgnoreCasts()->IgnoreParens()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::IntegerLiteralClass) {
                    int value = llvm::dyn_cast_or_null<clang::IntegerLiteral>(bop->getRHS()->IgnoreCasts()->IgnoreParens()->IgnoreCasts())->getValue().getLimitedValue();

                    if (value == 0) {
                        isNullAssignment = true;
                    }
                }
            }

            if(isSourceBuffer && isLastItem && isNullAssignment) {
                feature = "1";
                break;
            }
            else {
                isSourceBuffer = false;
                isLastItem = false;
                isNullAssignment = false;
            }
       }
    }

    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}