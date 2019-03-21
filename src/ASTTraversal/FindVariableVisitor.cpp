#include "ASTTraversal/FindVariableVisitor.h"

using namespace TOOBAD4ML;
using namespace ASTTraversal;

/**
 * m_variable is the buffer that might be overrun
 * @param declRefExpr
 */
cFindVariableVisitor::cFindVariableVisitor(clang::DeclRefExpr* declRefExpr) :
		m_variable(declRefExpr), m_found(false) {}


bool cFindVariableVisitor::VisitDeclRefExpr(clang::DeclRefExpr* declRefExpr) {

//		clang::ValueDecl* currentVar;
//		clang::ValueDecl* targetVar;
//
//		if (clang::ValueDecl* var = declRefExpr->getDecl()) {
//			if (var->getKind() == clang::Decl::Var) {
//				currentVar = var;
//			}
//		}
//		llvm::outs() << "Dentro de visitDeclRefExpr de findVariableVisitro3.\n";
//		declRefExpr->dumpColor();
//		llvm::outs() << "CAMBIO DE DUMPEOS A COLOR HEHE\n";
//
//		m_variable->dumpColor();
//		if (clang::ValueDecl* var = m_variable->getDecl()) { //PROBLEMS
//			if (var->getKind() == clang::Decl::Var) {
//				targetVar = var;
//			}
//		}
//
//		llvm::outs() << "Dentro de visitDeclRefExpr de findVariableVisitro4.\n";
//		if(currentVar == targetVar) {
//			m_found = true;
//		}
//
//		llvm::outs() << "Dentro de visitDeclRefExpr de findVariableVisitro5.\n";
//
//		return !m_found;

	return true;
}


bool cFindVariableVisitor::IsFound() {
	return m_found;
}
