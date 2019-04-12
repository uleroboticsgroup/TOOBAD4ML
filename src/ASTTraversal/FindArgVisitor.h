#ifndef SRC_ASTTRAVERSAL_FINDARGVISITOR_H_
#define SRC_ASTTRAVERSAL_FINDARGVISITOR_H_

#include <clang/AST/RecursiveASTVisitor.h>

namespace TOOBAD4ML {

namespace ASTTraversal {

class cFindArgVisitor: public  clang::RecursiveASTVisitor<cFindArgVisitor>{
public:
	cFindArgVisitor(clang::Expr *e);

	bool VisitDeclRefExpr(clang::Expr *e);

	bool VisitStringLiteral(clang::Expr *e);

private:

	std::vector<clang::Expr*> m_args;

};

} /* namespace TOOBAD4ML */

}/* namespace ASTTraversal */

#endif /* SRC_ASTTRAVERSAL_FINDARGVISITOR_H_ */
