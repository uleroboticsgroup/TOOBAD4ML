#ifndef SRC_CORE_BUFFER_OVERFLOW_H_
#define SRC_CORE_BUFFER_OVERFLOW_H_

#include <clang/AST/Expr.h>

namespace TOOBAD4ML {

namespace description {

class cCodePseudoPropertyGraph;

/*!
 *
 */
class cBufferOverflow {
public:

	/*!
	 * Constructor
	 * @param The AST Expr Node representing the actual buffer
	 * overflow vulnerability, AKA the sink node.
	 */
	cBufferOverflow(clang::Expr&);

	/*!
	 *	Getter for retrieving the node that represent the BOF
	 *	vulnerability. The buffer that could be overflowed/overriden.
	 * @return DeclRefExpr
	 */
	clang::DeclRefExpr* GetBuffer();

	/*!
	 * Returns the vector of actual nodes that represent an input call
	 * related to the buffer.
	 * @return Vector of CallExpr
	 */
	std::vector<clang::CallExpr*> GetInput();

	/*!
	 * Getter for retrieving the actual node where the vulnerability
	 * happens. This could be either a BinaryOperator or a CallExpr, both
	 * of them given as Expr.
	 * @return Expr
	 */
	clang::Expr* GetSink();

	/*!
	 *	Getter for retrieving the actual sink node type. Since GetSink()
	 *	always return Expr, its original type can be obtaind via this
	 *	getter.
	 * @return StmtClass
	 */
	clang::Stmt::StmtClass GetSinkType();

	/*!
	 * Given the pseudo-property-graph, traverses it trying to find all
	 * those nodes corresponding to input functions calls. Traversing and
	 * finding is carried out by internal class called cFindInputNodes.
	 * Within that class, () operator is overwritten.
	 */
	void SetInput(cCodePseudoPropertyGraph&);

private:

	//!
	clang::Expr* m_sink;

	//!
	clang::DeclRefExpr* m_buffer;

	//!
	std::vector<clang::CallExpr*> m_input;

}; /* cBufferOverflow */

//!
typedef std::vector<cBufferOverflow> BOFList;

} /* namespace description */

} /* namespace TOOBAD4ML */

#endif /* SRC_CORE_BUFFER_OVERFLOW_H_ */
