#ifndef SRC_AST_TRAVERSAL_FINDSELECTED_AST_NODES_VISITOR_H_
#define SRC_AST_TRAVERSAL_FINDSELECTED_AST_NODES_VISITOR_H_


#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"


namespace TOOBAD4ML {

namespace ASTTraversal {

/*!
 * This class transforms the received vulnerable BOFLocation lines to
 * actual AST Nodes in form of Expr nodes.
 */
class cFindSelectedASTNodesVisitor: public clang::RecursiveASTVisitor<
		cFindSelectedASTNodesVisitor> {

public:

	/*!
	 *	Constructor receives the BOFLocation vector and creates a copy of
	 *	it for inner checkings.
	 * @param
	 */
	cFindSelectedASTNodesVisitor(std::vector<BOFLocation>&);

	/*!
	 *	Getter
	 * @return Vulnerable AST nodes vector
	 */
	std::vector<clang::Expr*> GetSelectedNodes();

	/*!
	 * Traverses every single Call Expresion Node inside the given
	 * FunctionDecl for which this visitor was called.
	 * @param The actual CallExpr node being traversed
	 * @return isvulnerable
	 */
	bool VisitCallExpr(clang::CallExpr*);

	/*!
	 * Traverses every single Call Expresion Node inside the given
	 * FunctionDecl for which this visitor was called.
	 * @param The actual Binaryoperator node being traversed
	 * @return isVulnerable
	 */
	bool VisitBinaryOperator(clang::BinaryOperator*);

private:

	/*!
	 * Checks whether the node being traversed at the moment is
	 * vulnerable. It iterates over all the elements of the
	 * given BOFLocation vector and compares the first element
	 * with the start SourceLocation of the node and the second
	 * element with the end SourceLocation of the node. If they're
	 * equal, the node is being pushed into m_selectedNodes as an
	 * Expr node and the BOFLocation element is deleted from its
	 * respective vector. This way we get the EXACT node that
	 * represents the vulnerable call or assignment.
	 *
	 * @param The node being traversed right now, passed as Expr Node
	 * since Expr is parent class of both CallExpr and BinaryOperator
	 * @return False is BOFLocation vector m_vulnerableLines is empty,
	 * otherwise true.
	 */
	bool isVulnerable(clang::Expr*);


	//! Vector of actual vulnerable AST Expr nodes.
	std::vector<clang::Expr*> m_selectedNodes;

	//! A copy of BOFLocation vector received as constructor argument.
	std::vector<BOFLocation>& m_vulnerableLines;

}; /* cFindSelectedASTNodesVisitor */

} /* namespace ASTTraversal */

} /* namespace TOOBAD4ML */


#endif /* SRC_AST_TRAVERSAL_FIND_SELECTED_AST_NODES_VISITOR_H */
