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

enum BufferType {
    SRC,
    DST
};

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
    cBufferOverflow(clang::Expr*, clang::DeclRefExpr*, clang::DeclRefExpr*, std::vector<clang::CallExpr*>, std::vector<clang::Expr*>);
    ~cBufferOverflow();


    // CLASS METHODS
    // ------------------------------------------------------------------------

public:

    // ACCESSOR METHODS
    // ------------------------------------------------------------------------

public:

	clang::Expr* GetSink();

	clang::DeclRefExpr* GetBuffer(BufferType);

	std::vector<clang::CallExpr*> GetInput();

    std::vector<clang::Expr*> GetSinkSanitizations();
    
    // ATTRIBUTES
    // ------------------------------------------------------------------------

private:

	//! AST node of the statement that triggered the vulnerability.
	clang::Expr* m_sink;

	//! AST node of the variable representing a memory region (i.e. array), in
    /// which the vulnerable instruction reads.
	clang::DeclRefExpr* m_srcBuffer;

    //! AST node of the variable representing a memory region (i.e. array), in
    /// which the vulnerable instruction writes.
	clang::DeclRefExpr* m_dstBuffer;

	//! List of AST nodes containing statements involved in reading input data,
    /// that affects {\ref m_buffer}.
	std::vector<clang::CallExpr*> m_input;

    //! List of AST nodes where sanitizations related to the sink are performed.
    std::vector<clang::Expr*> m_sinkSanitizations;

}; /* cBufferOverflow */


// ALIAS DEFINITIONS
// ----------------------------------------------------------------------------

typedef std::vector<cBufferOverflow> BOFList;


} // namespace description

} // namespace TOOBAD4ML

// ----------------------------------------------------------------------------
#endif
