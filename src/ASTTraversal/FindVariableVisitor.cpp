#include "ASTTraversal/FindVariableVisitor.h"

using namespace TOOBAD4ML;
using namespace ASTTraversal;

/**
 * m_variable is the buffer that might be overrun
 * @param declRefExpr
 */
cFindVariableVisitor::cFindVariableVisitor(clang::Expr* declRefExpr) :
		m_buffer(declRefExpr), m_found(false) {}


bool cFindVariableVisitor::VisitDeclRefExpr(clang::Stmt* S) {

//		llvm::outs() << "dentro VISITOR\n";
//		S->dumpColor();

		clang::ValueDecl* currentVar;
		clang::ValueDecl* targetVar;

		clang::FunctionDecl* targetFunc;

		if(clang::DeclRefExpr* Ref = llvm::dyn_cast_or_null<clang::DeclRefExpr>(m_buffer) ) {
			if(clang::VarDecl* VD = llvm::dyn_cast_or_null<clang::VarDecl>(Ref->getDecl())) {
				//llvm::outs() << "current\n";
				currentVar = VD;
			}
		}

		if(clang::DeclRefExpr* Ref = llvm::dyn_cast<clang::DeclRefExpr>(S) ) {
			  if(clang::VarDecl* VD = llvm::dyn_cast<clang::VarDecl>(Ref->getDecl())) {
				   //llvm::outs() << "target\n";
				   targetVar = VD;
				   if(currentVar == targetVar) {
					   m_found = true;
					   return false;
				   }
			  }
		}

	return true;
}


bool cFindVariableVisitor::IsFound() {
	return m_found;
}
