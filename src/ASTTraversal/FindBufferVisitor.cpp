#include "ASTTraversal/FindBufferVisitor.h"

using namespace TOOBAD4ML;
using namespace ASTTraversal;

cFindBufferVisitor::cFindBufferVisitor(clang::Expr* e) : m_buffer(0) {}


bool cFindBufferVisitor::VisitMemberExpr(clang::Expr* e) {

	clang::QualType t = e->getType();

	if(clang::MemberExpr *m = llvm::dyn_cast<clang::MemberExpr>(e)) {
		m_buffer = m;
	}
	return true;
}


bool cFindBufferVisitor::VisitDeclRefExpr(clang::Expr* e) {

//	llvm::outs() << t.getAsString() << "\n";
//	llvm::outs() << t.getTypePtr()->isStructureType() << "\n";

	if(clang::DeclRefExpr *ref = llvm::dyn_cast<clang::DeclRefExpr>(e)) {
		clang::QualType t = e->getType();

		// if the DeclRefExpr is of type Array
		if(t.getTypePtr()->isArrayType()) {
			//decl->dumpColor();
			//t->getSize().dump();

			if(m_buffer == NULL){
				m_buffer = e;
				return false;
			}

		 }
	}

	return true;
}

clang::Expr* cFindBufferVisitor::getBuffer() {
	return m_buffer;
}

int cFindBufferVisitor::getA() {
	return a;
}
