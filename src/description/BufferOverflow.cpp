// ----------------------------------------------------------------------------
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "ASTTraversal/FindVariableVisitor.h"
/// ----------------------------------------------------------------------------
#include <llvm/Support/Casting.h>
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;
// ----------------------------------------------------------------------------
// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cBufferOverflow::cBufferOverflow(clang::Expr* sink, clang::DeclRefExpr* dstBuffer,clang::DeclRefExpr* srcBuffer, std::vector<clang::CallExpr*> inputs) :
		m_sink(sink), 
		m_dstBuffer(dstBuffer),
		m_srcBuffer(srcBuffer),
		m_input(inputs) {}

cBufferOverflow::~cBufferOverflow() {
}


// ACCESSOR METHODS
// ----------------------------------------------------------------------------

clang::Expr* cBufferOverflow::GetSink() {
	return m_sink;
}

clang::DeclRefExpr* cBufferOverflow::GetBuffer(BufferType bufferType) {
	return bufferType == BufferType::DST ? m_dstBuffer : m_srcBuffer;
}

std::vector<clang::CallExpr*> cBufferOverflow::GetInput() {
	return m_input;
}
