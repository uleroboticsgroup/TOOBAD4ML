#ifndef SRC_AST_TRAVERSAL_FINDSTMTVISITOR_H_
#define SRC_AST_TRAVERSAL_FINDSTMTVISITOR_H_

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Analysis/CFG.h>

namespace TOOBAD4ML {

namespace ASTTraversal {

/*!
 *
 */
class cFindStmtVisitor: public clang::RecursiveASTVisitor<
		cFindStmtVisitor> {

public:

	/*!
	 *
	 * @param
	 */
	cFindStmtVisitor(std::vector<clang::CFGStmt>);

	/*!
	 *
	 * @param
	 * @return
	 */
	bool VisitCallExpr(clang::CallExpr*);

	/*!
	 *
	 * @return
	 */
	clang::CallExpr* CallExprFound();

private:
    //!
	std::vector<clang::CallExpr*> m_targetCallExprs;

    //!
	clang::CallExpr* m_callExprFound;

}; /* cFindStmtVisitor  */

} /* namespace ASTTraversal */

} /* namespace TOOBAD4ML */

#endif /* SRC_AST_TRAVERSAL_FINDVARIABLEVISITOR_H_ */
