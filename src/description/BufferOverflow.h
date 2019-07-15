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
    cBufferOverflow(clang::Expr*, clang::DeclRefExpr*, std::vector<clang::CallExpr*>);
    ~cBufferOverflow();


    // CLASS METHODS
    // ------------------------------------------------------------------------

public:

    // ACCESSOR METHODS
    // ------------------------------------------------------------------------

public:

	clang::Expr* GetSink();

	clang::DeclRefExpr* GetBuffer();

	std::vector<clang::CallExpr*> GetInput();

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
