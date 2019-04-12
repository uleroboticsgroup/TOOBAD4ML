
#include "ASTTraversal/FindFunctionVisitor.h"

using namespace TOOBAD4ML;
using namespace ASTTraversal;

cFindFunctionVisitor::cFindFunctionVisitor(clang::Expr *e) {};

bool cFindFunctionVisitor::VisitDeclRefExpr(clang::Expr *e) {

	if(clang::DeclRefExpr *ref = llvm::dyn_cast<clang::DeclRefExpr>(e)) {
		if(clang::FunctionDecl *fun  = llvm::dyn_cast<clang::FunctionDecl>(ref->getDecl())) {

			m_function = fun;

			//llvm::outs() <<  "SINK\n";

			//m_function->dumpColor();

			if(clang::ValueDecl* value = ref->getDecl()) {
				//llvm::outs() <<  "VALUEDECL" << value->getName() << "\n";
				//e->dumpColor();
				m_functionName = value->getName();

			}
		}

	}


	return true;
}


std::string cFindFunctionVisitor::getFunctionName() {
	return m_functionName;
}

clang::FunctionDecl* cFindFunctionVisitor::getFunctionDecl() {
	return m_function;
}
