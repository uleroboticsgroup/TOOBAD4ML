#include "ASTTraversal/FindVariableVisitor.h"
using namespace TOOBAD4ML;
using namespace ASTTraversal;

clang::VarDecl* getTargetVarDecl(clang::DeclRefExpr* targetDeclRefExpr) {
	return (targetDeclRefExpr) ? llvm::dyn_cast<clang::VarDecl>(targetDeclRefExpr->getDecl()): nullptr;
}
/**
 * m_variable is the buffer that might be overrun
 * @param declRefExpr
 */
cFindVariableVisitor::cFindVariableVisitor(clang::DeclRefExpr* declRefExpr) :
		m_targetVariable(getTargetVarDecl(declRefExpr)), m_found(false) {}


bool cFindVariableVisitor::VisitDeclRefExpr(clang::DeclRefExpr* currentDeclRefExpr) {
	clang::VarDecl* currentVarDecl = llvm::dyn_cast<clang::VarDecl>(currentDeclRefExpr->getDecl());
	if(currentVarDecl == m_targetVariable) {
		m_found = true;
	}
		
	return !m_found;

}
bool cFindVariableVisitor::IsFound() {
	return m_found;
}
