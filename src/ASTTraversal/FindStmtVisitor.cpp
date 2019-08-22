#include "ASTTraversal/FindStmtVisitor.h"
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace ASTTraversal;
// ----------------------------------------------------------------------------
std::vector<clang::CallExpr*> getCallExprs(std::vector<clang::CFGStmt> stmts) {
    std::vector<clang::CallExpr*> targetCallExprs;

    for(clang::CFGStmt stmt: stmts) {
        clang::CallExpr* callExpr = const_cast<clang::CallExpr*>(llvm::dyn_cast<clang::CallExpr>(stmt.getStmt()));
        targetCallExprs.push_back(callExpr);
    }

    return targetCallExprs;
}

// CONSTRUCTORS & DESTRUCTORS
// ------------------------------------------------------------------------

cFindStmtVisitor::cFindStmtVisitor(std::vector<clang::CFGStmt> targetCallExprs) :
		m_targetCallExprs(getCallExprs(targetCallExprs)), m_callExprFound(nullptr) {}

// CLASS METHODS
// ------------------------------------------------------------------------

bool cFindStmtVisitor::VisitCallExpr(clang::CallExpr* currentCallExpr) {
    for(clang::CallExpr* targetCallExpr: m_targetCallExprs) {
        if (targetCallExpr == currentCallExpr) {
            m_callExprFound = currentCallExpr;
            break;
        }
    }

	return !m_callExprFound;

}
clang::CallExpr* cFindStmtVisitor::CallExprFound() {
	return m_callExprFound;
}
