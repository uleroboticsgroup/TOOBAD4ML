// ----------------------------------------------------------------------------
#ifndef TOOBAD4ML_DESCRIPTION_BUFFEROVERFLOW_H
#define TOOBAD4ML_DESCRIPTION_BUFFEROVERFLOW_H
// ----------------------------------------------------------------------------
#include <clang/AST/Expr.h>
// ----------------------------------------------------------------------------


namespace TOOBAD4ML {

namespace description {


// CLASS FORWARDING
// ----------------------------------------------------------------------------

class cCodePropertyGraph;


// CLASS DEFINITION
// ----------------------------------------------------------------------------

/*!
 * \class cBufferOverflow
 *
 * \brief
 * A representation of a Buffer Overflow vulnerability in terms of AST nodes.
 *
 * \details
 * A Buffer Overflow (BOF) is a condition that exists when a program attempts
 * to access through an array a memory location that is outside its boundaries.
 * This class encapsulates all the data assumed to be related to such
 * vulnerability. The data is comprised of statements and variables from
 * the source code, which are extracted by searching for patterns in a Code
 * Property Graph using the sink statement; that is, the statement where the
 * vulnerability originated.
 */
class cBufferOverflow {

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------

public:

	/*!
	 * Creates a Buffer Overflow representation.
     *
	 * @param sink  AST node of the statement where the BOF originally
     *              occurred.
	 */
	cBufferOverflow(clang::Expr&);

    ~cBufferOverflow();


    // CLASS METHODS
    // ------------------------------------------------------------------------

public:

	clang::Stmt::StmtClass GetSinkType();


    // ACCESSOR METHODS
    // ------------------------------------------------------------------------

public:

	clang::Expr* GetSink();

	clang::DeclRefExpr* GetBuffer();

	std::vector<clang::CallExpr*> GetInput();

	/*!
     * Stores all AST nodes corresponding to input function calls by traversing
     * a Control Flow Graph (CFG) where the BOF is present.
     * TODO: change CPG for CFG??
     *
     * @param cfg   CFG in which to search for input node patterns.
	 */
	void SetInput(cCodePropertyGraph&);


    // ATTRIBUTES
    // ------------------------------------------------------------------------

private:

	//! AST node of the statement that triggered the vulnerability.
	clang::Expr* m_sink;

	//! AST node of the variable representing a memory region (i.e. array), in
    /// which the vulnerability occurred.
	clang::DeclRefExpr* m_buffer;

	//! List of AST nodes containing statements involved in reading input data,
    /// that affects {\ref m_buffer}.
	std::vector<clang::CallExpr*> m_input;

}; /* cBufferOverflow */


// ALIAS DEFINITIONS
// ----------------------------------------------------------------------------

typedef std::vector<cBufferOverflow> BOFList;


} // namespace description

} // namespace TOOBAD4ML

// ----------------------------------------------------------------------------
#endif
