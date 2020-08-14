#include "description/Reach.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
#include "ASTTraversal/FindVariableVisitor.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cReach::cReach(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

std::string isInside(clang::Stmt* stmt, clang::DeclRefExpr* targetIndex) {
    if (stmt->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
        clang::BinaryOperator* bop = llvm::dyn_cast<clang::BinaryOperator>(stmt);
        if (bop->getLHS()->IgnoreCasts()->IgnoreParens()->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
            clang::DeclRefExpr* bopVariable = llvm::dyn_cast<clang::DeclRefExpr>(bop->getLHS()->IgnoreCasts()->IgnoreParens());

            if (bopVariable->getDecl() == targetIndex->getDecl()) {
                return "1";
            }
        }
    }
    else if (stmt->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass) {
        clang::UnaryOperator* uop = llvm::dyn_cast<clang::UnaryOperator>(stmt);
        if (uop->getSubExpr()->IgnoreCasts()->IgnoreParens()->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
            clang::DeclRefExpr* uopVariable = llvm::dyn_cast<clang::DeclRefExpr>(uop->getSubExpr()->IgnoreCasts()->IgnoreParens());

            if (uopVariable->getDecl() == targetIndex->getDecl()) {
                return "1";
            }
        }
    }

    return "0";
}


// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cReach::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    std::string feature = "-1";
    int found = -1; // 0 FOR, 1 WHILE

    clang::DeclRefExpr* targetIndex; 
    clang::Expr* expr = bof.GetSink();
    const clang::Stmt* stmt = const_cast<clang::Stmt*>(llvm::dyn_cast<clang::Stmt>(expr));
    const clang::Stmt* parent;

    // Is it been access with a variables as index? Lest's find out
    if (expr->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
        clang::BinaryOperator* bop = llvm::dyn_cast<clang::BinaryOperator>(expr);

        if(bop->getLHS()->IgnoreCasts()->IgnoreParens()->getStmtClass() == clang::Stmt::StmtClass::ArraySubscriptExprClass) {
            clang::ArraySubscriptExpr* dstExpr = llvm::dyn_cast<clang::ArraySubscriptExpr>(bop->getLHS()->IgnoreCasts()->IgnoreParens());

            if(dstExpr->getRHS()->IgnoreCasts()->IgnoreParens()->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
                targetIndex = llvm::dyn_cast<clang::DeclRefExpr>(dstExpr->getRHS()->IgnoreCasts()->IgnoreParens());
            }
        }
    }

    if(targetIndex){
        feature = "0";
        while(stmt && found == -1) {
            const auto& parents = cpg.GetAST().getASTContext().getParents(*stmt);
            if (!parents.empty()) {
                parent = parents[0].get<clang::Stmt>();
            }

            if (parent && parent->getStmtClass() == clang::Stmt::StmtClass::WhileStmtClass) {
                found = 1;
                break;
            }
            else if (parent && parent->getStmtClass() == clang::Stmt::StmtClass::ForStmtClass) {
                found = 0;
            }

            stmt = parent;
        }

        switch (found) {
            case 0: { //FOR
                clang::ForStmt* forStmt = llvm::dyn_cast<clang::ForStmt>(const_cast<clang::Stmt*>(parent));
                clang::Expr* increment = llvm::dyn_cast<clang::Expr>(forStmt->getInc());
                ASTTraversal::cFindVariableVisitor visitor(targetIndex);
                visitor.TraverseStmt(increment);
                if (visitor.IsFound()) {
                    feature = "1";
                }
            }
            break;
            case 1: { //WHILE
                clang::WhileStmt* whileStmt = llvm::dyn_cast<clang::WhileStmt>(const_cast<clang::Stmt*>(parent));
                clang::Stmt* whileBody = whileStmt->getBody();

                if (whileBody->getStmtClass() == clang::Stmt::StmtClass::CompoundStmtClass){
                    clang::CompoundStmt* compoundWhileBody = llvm::dyn_cast<clang::CompoundStmt>(whileBody);

                    for(int i = 0; i < compoundWhileBody->size(); i++) {
                        feature = isInside(compoundWhileBody->body_begin()[i], targetIndex);

                        if (feature == "1") {
                            break;
                        }                    }
                }
                else {
                    feature = isInside(whileBody, targetIndex);
                }
            }
        }
   
    }
    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
