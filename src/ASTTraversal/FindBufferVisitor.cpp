
#include "ASTTraversal/FindBufferVisitor.h"

using namespace TOOBAD4ML;
using namespace ASTTraversal;

cFindBufferVisitor::cFindBufferVisitor(clang::Expr* decl) : m_buffer(0) {}

bool cFindBufferVisitor::VisitDeclRefExpr(clang::Expr* decl) {


	if (auto t =  llvm::dyn_cast_or_null<clang::ConstantArrayType>(decl->getType().getTypePtr())) {
		//decl->dumpColor();
		//t->getSize().dump();
		m_buffer = llvm::dyn_cast<clang::DeclRefExpr>(decl);
		return false;
	 }

	return true;
}

clang::DeclRefExpr* cFindBufferVisitor::getBuffer() {
	return m_buffer;
}
