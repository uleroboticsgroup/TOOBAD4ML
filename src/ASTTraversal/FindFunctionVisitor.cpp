
#include "ASTTraversal/FindFunctionVisitor.h"

namespace TOOBAD4ML {

namespace ASTTraversal {


	cFindFunctionVisitor::cFindFunctionVisitor(clang::Expr *e) {};

	bool cFindFunctionVisitor::VisitDeclRefExpr(clang::Expr *e) {

		if(clang::DeclRefExpr *ref = llvm::dyn_cast<clang::DeclRefExpr>(e)) {
			if(clang::FunctionDecl *fun  = llvm::dyn_cast<clang::FunctionDecl>(ref->getDecl())) {

				m_function = ref;

				if(clang::ValueDecl* var = ref->getDecl()) {
					//llvm::outs() << var->getName() << "\n";
					//e->dumpColor();
					m_functionName = var->getName();
				}
			}
		}

		return false;
	}

	std::string cFindFunctionVisitor::getFunctionName() {
		return m_functionName;
	}

} /* namespace ASTTraversal */

} /* namespace TOOBAD4ML */
