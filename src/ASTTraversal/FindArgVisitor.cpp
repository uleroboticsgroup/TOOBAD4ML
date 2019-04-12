#include "ASTTraversal/FindArgVisitor.h"

using namespace TOOBAD4ML;

using namespace ASTTraversal;


bool cFindArgVisitor::VisitDeclRefExpr(clang::Expr *e) {

	if(clang::DeclRefExpr *ref = llvm::dyn_cast<clang::DeclRefExpr>(e)) {

		if(clang::VarDecl *var  = llvm::dyn_cast<clang::VarDecl>(ref->getDecl())) {

			m_args.push_back(e);
		}

	}

	return true;
}

bool cFindArgVisitor::VisitStringLiteral(clang::Expr *e) {

	m_args.push_back(e);

	return true;
}
