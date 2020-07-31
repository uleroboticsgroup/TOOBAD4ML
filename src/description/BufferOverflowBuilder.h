// ----------------------------------------------------------------------------
#ifndef TOOBAD4ML_DESCRIPTION_BUFFEROVERFLOWBUILDER_H
#define TOOBAD4ML_DESCRIPTION_BUFFEROVERFLOWBUILDER_H
// ----------------------------------------------------------------------------
#include <clang/AST/Expr.h>
#include "description/CodePropertyGraph.h"
#include "description/BufferOverflow.h"
// ----------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {
// ----------------------------------------------------------------------------
class cCodePropertyGraph;
// ----------------------------------------------------------------------------
/*!
 * \class cBufferOverflowBuilder
 *
 * \brief
 * A utility to construct a BufferOverflow object.
 *
 * \details
 * This class is a factory to build a <CODE>TOOBAD4ML::description::cBufferOverflow</CODE>.
 * It obtains the source and destination buffer, the sink sanitizations and the inputs
 * that affects the buffer/s of the sink. 
 * Finally, creates the BufferOverflow object itself.
 */
class cBufferOverflowBuilder {

// CLASS METHODS
// ------------------------------------------------------------------------
public:
    /*!
     * Creates a BufferOverflow object
     *
     * @param sink The sink of the vulnerability.
     * @param cpg The Code Property Graph associated with the sink.
     * @returns A BufferOverflow object
     * */
    cBufferOverflow& CreateBufferOverflow(clang::Expr&, cCodePropertyGraph&);

// ATTRIBUTES
// ------------------------------------------------------------------------
private:
    
    /*!
     * It obtains the inputs associated with the sink's destination buffer.
     *
     * @param buffer The destination buffer.
     * @param spg The SinkPathGraph associated with the sink.
     * @returns A list of all the CallExpr which are inputs for the buffer.
     * */
    std::vector<clang::CallExpr*> getInputs(clang::DeclRefExpr&, SinkPathGraph);
    
    /*!
     * It obtains one of the sink's buffers.
     *
     * @param sink The sink of the vulnerability.
     * @param bufferType The type of the buffer (BufferType::DST (destination), BufferType::SRC (source))
     * @returns The buffer
     * */
    clang::DeclRefExpr* getBuffer(clang::Expr&, BufferType);
    
    /*!
     * It obtains the nodes where some kind of sanitization is performed related to the sink's buffers.
     *
     * @param dstBuffer The destination buffer
     * @param srcBuffer The source buffer
     * @param spg The sink path graph of the sink.
     * @returns A list of all the Exprs that are sanitizations.
     * */   
    std::vector<clang::Expr*> getSinkSanitizations(clang::DeclRefExpr*, clang::DeclRefExpr*, SinkPathGraph, cCodePropertyGraph&);
};

}

}

#endif