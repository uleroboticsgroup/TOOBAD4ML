
#ifndef SRC_ASTTRAVERSAL_FINDBUFFERVISITOR_H_
#define SRC_ASTTRAVERSAL_FINDBUFFERVISITOR_H_

#include <clang/AST/RecursiveASTVisitor.h>

namespace TOOBAD4ML {

namespace ASTTraversal {

class cFindBufferVisitor : public clang::RecursiveASTVisitor<cFindBufferVisitor>{

public:

	cFindBufferVisitor(clang::Expr* e);

	bool VisitMemberExpr(clang::Expr* e);

	bool VisitDeclRefExpr(clang::Expr* e);

	clang::Expr* getBuffer();

private:
	clang::Expr* m_buffer;

};

} /* namespace ASTTraversal */

}/* namespace TOOBAD4ML */

#endif /* SRC_ASTTRAVERSAL_FINDBUFFERVISITOR_H_ */
