#ifndef SRC_AST_TRAVERSAL_FINDSTMTVISITOR_H_
#define SRC_AST_TRAVERSAL_FINDSTMTVISITOR_H_
// ----------------------------------------------------------------------------
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Analysis/CFG.h>
// ----------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace ASTTraversal {

/*!
 * \class cFindStmtVisitor
 * 
 * \brief
 * A visitor which searchs for the target call expressions
 * 
 * \details
 * This class is a wrapper for <CODE>clang::RecursiveASTVisitor<T></CODE>.
 * It searchs trough all the AST finding the CallExpressions and calling with them
 * the method VisitCallExpr where we check if the one that the visitor found is one
 * of the ones we are looking for.
 * 
 */
class cFindStmtVisitor: public clang::RecursiveASTVisitor<
		cFindStmtVisitor> {

// CONSTRUCTORS & DESTRUCTORS
// ------------------------------------------------------------------------
public:

	/*!
	 * Constructor
	 * @param stmts The stmts which contain the CallExpressions we want to look for.
	 */
	cFindStmtVisitor(std::vector<clang::CFGStmt>);

// CLASS METHODS
// ------------------------------------------------------------------------
public:
	/*!
	 * Callback called every time the visitor finds a CallExpr.
	 * @param currentCallExpr The CallExpr the visitor found.
	 * @return true if we want to keep searching, false if we found one.
	 */
	bool VisitCallExpr(clang::CallExpr*);

	/*!
	 * Getter for m_callExprFound
	 * @return m_callExprFound
	 */
	clang::CallExpr* CallExprFound();

// ATTRIBUTES
// ------------------------------------------------------------------------
private:
    //! The CallExprs we are looking for
	std::vector<clang::CallExpr*> m_targetCallExprs;

    //! If we found one of the above CallExpr, we store it here.
	clang::CallExpr* m_callExprFound;

}; /* cFindStmtVisitor  */

} /* namespace ASTTraversal */

} /* namespace TOOBAD4ML */

#endif /* SRC_AST_TRAVERSAL_FINDVARIABLEVISITOR_H_ */
