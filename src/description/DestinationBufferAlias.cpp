#include "description/DestinationBufferAlias.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
#include "ASTTraversal/FindVariableVisitor.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cDestinationBufferAlias::cDestinationBufferAlias(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cDestinationBufferAlias::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    std::string feature = "0";

    cExprUtils* exprUtils = cExprUtils::GetInstance();
    SinkPathGraph spg = cpg.GetSPG(*(bof.GetSink()));
    clang::DeclRefExpr* dstBuffer = bof.GetBuffer(BufferType::DST);

    if(dstBuffer){
        for(clang::CFGStmt cfgStmt: spg) {
    		clang::Stmt* stmt = const_cast<clang::Stmt*>(cfgStmt.getStmt());

            if (stmt->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* bop = llvm::dyn_cast<clang::BinaryOperator>(stmt);

                ASTTraversal::cFindVariableVisitor dstVisitor(dstBuffer);
                dstVisitor.TraverseStmt(bop->getRHS());

                if (dstVisitor.IsFound()) {
                    if (bop->getRHS()->IgnoreCasts()->IgnoreParens()->getStmtClass() != clang::Stmt::StmtClass::ArraySubscriptExprClass) {
                        if (bop->getLHS()->IgnoreCasts()->IgnoreParens()->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) { 
                            clang::DeclRefExpr* target = llvm::dyn_cast<clang::DeclRefExpr>(bop->getLHS()->IgnoreCasts()->IgnoreParens());

                            if (target->getType().getTypePtr()->isArrayType() || target->getType().getTypePtr()->isPointerType()) {
                                feature = "1";
                            }
                        }
                    } 
                }

            }
       }
    }

    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
