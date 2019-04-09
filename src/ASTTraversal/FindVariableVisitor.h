#ifndef SRC_AST_TRAVERSAL_FINDVARIABLEVISITOR_H_
#define SRC_AST_TRAVERSAL_FINDVARIABLEVISITOR_H_

#include <clang/AST/RecursiveASTVisitor.h>

namespace TOOBAD4ML {

namespace ASTTraversal {

/*!
 *
 */
class cFindVariableVisitor: public clang::RecursiveASTVisitor<
		cFindVariableVisitor> {

public:

	/*!
	 *
	 * @param
	 */
	cFindVariableVisitor(clang::Expr*);

	/*!
	 *
	 * @param
	 * @return
	 */
	bool VisitDeclRefExpr(clang::Stmt*);

	/*!
	 *
	 * @return
	 */
	bool IsFound();

private:

    //!
	clang::Expr* m_buffer;

    //!
	bool m_found;

}; /* cFindVariableVisitor  */

} /* namespace ASTTraversal */

} /* namespace TOOBAD4ML */

#endif /* SRC_AST_TRAVERSAL_FINDVARIABLEVISITOR_H_ */
