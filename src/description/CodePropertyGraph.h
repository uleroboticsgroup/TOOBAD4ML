// ----------------------------------------------------------------------------
#ifndef TOOBAD4ML_DESCRIPTION_CODEPROPERTYGRAPH_H
#define TOOBAD4ML_DESCRIPTION_CODEPROPERTYGRAPH_H
// ----------------------------------------------------------------------------
#include <clang/AST/Decl.h>
#include <clang/Analysis/CFG.h>
// ----------------------------------------------------------------------------


namespace TOOBAD4ML {

namespace description {

/*!
 * \class cCodePropertyGraph
 *
 * \brief
 * A representation of the body of a function in terms of source code and flow
 * of control.
 *
 * \details
 * This class encapsulates several representations of a function code snippet
 * that are useful for finding patterns. Particularly, it contains a joint
 * graph representation of the body of such function (both in syntactic and
 * semantic terms): the AST (Abstract Syntax Tree) and the CFG (Control Flow
 * Graph). Please note that the CFG is built from the AST provided by Clang.
 */
class cCodePropertyGraph {

    // CONSTRUCTOR & DESTRUCTOR
    // ------------------------------------------------------------------------

public:

	/*!
     * Creates a Code Property Graph given the AST representation of a
     * function.
     *
	 * @param functionDecl  Root AST node of a function
	 */
	cCodePropertyGraph(clang::FunctionDecl&);

    ~cCodePropertyGraph();


    // ACCESSOR METHODS
    // ------------------------------------------------------------------------

public:

	const clang::FunctionDecl& GetAST();

	const clang::CFG& GetCFG();


    // ATTRIBUTES
    // ------------------------------------------------------------------------

private:

    //! Root AST node of a function.
	clang::FunctionDecl& m_AST;

    //! CFG of a function.
	std::unique_ptr<clang::CFG> m_CFG;

}; /* class cCodePropertyGraph */

} // namespace description

} // namespace TOOBAD4ML

// ----------------------------------------------------------------------------
#endif
