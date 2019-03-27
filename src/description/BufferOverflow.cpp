// ----------------------------------------------------------------------------
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "ASTTraversal/FindVariableVisitor.h"
#include "ASTTraversal/FindBufferVisitor.h"
/// ----------------------------------------------------------------------------
#include <llvm/Support/Casting.h>
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;
// ----------------------------------------------------------------------------


//TODO: move this class out of this file.
/*!
 * This class is called with CFG.VisitBlockStmts. That is,
 * given a CFG, clang will internally call this class each time
 * it traverses a basic block, for each statement.
 */
class cFindInputNodes {
public:

	cFindInputNodes(clang::Expr* declRef, clang::CFG& CFG) :
			m_buffer(declRef), m_cfg(CFG) {
	}

	void operator()(const clang::Stmt* stmt) {

		clang::Stmt* aux = const_cast<clang::Stmt*>(stmt);
		switch (aux->getStmtClass()) {

		case clang::Stmt::StmtClass::CallExprClass: {

			ASTTraversal::cFindVariableVisitor m_visitor(m_buffer);

			//llvm::outs() << "IMPRIMIENDO DESDE CFINDINPUTNODES.\n";
			//m_buffer->dumpColor();

			m_visitor.TraverseStmt(aux);

			if (m_visitor.IsFound()) {

				m_input.push_back(llvm::cast<clang::CallExpr>(aux));

			}

		}

			break;

		case clang::Stmt::StmtClass::BinaryOperatorClass: { /*
		 if(inputClassificationtypes.find(llvm::cast<clang::CallExpr>(aux)->getDirectCallee()->getNameAsString()) != inputClassificationtypes.end()){
		 ASTTraversal::cFindVariableVisitor m_visitor(m_buffer);
		 m_visitor.TraverseStmt(const_cast<clang::Stmt*>(aux));

		 if (m_visitor.isFound()) {
		 //TODO Get right handed side of binaryoperator
		 //m_input.push_back(llvm::cast<clang::CallExpr>(aux));
		 }
		 }*/
		}

			break;
		default: {

		}
			break;
		}

	}

	std::vector<clang::CallExpr*> GetInput() {
		return m_input;
	}

private:

	clang::Expr* m_buffer;
	std::vector<clang::CallExpr*> m_input;
	clang::CFG& m_cfg;

};


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cBufferOverflow::cBufferOverflow(clang::Expr& sink) :
		m_sink(&sink), m_buffer(0) {

	ASTTraversal::cFindBufferVisitor m_visitor(m_sink);

	m_visitor.TraverseStmt(m_sink);

	m_buffer = m_visitor.getBuffer();

	llvm::outs() << "ESTE ES EL BUFFER\n";
	m_buffer->dump();

}

cBufferOverflow::~cBufferOverflow() {
}


// CLASS METHODS
// ----------------------------------------------------------------------------

clang::Stmt::StmtClass cBufferOverflow::GetSinkType() {
	return m_sink->getStmtClass();
}

// ACCESSOR METHODS
// ----------------------------------------------------------------------------

clang::Expr* cBufferOverflow::GetSink() {
	return m_sink;
}

clang::Expr* cBufferOverflow::GetBuffer() {
	return m_buffer;
}

std::vector<clang::CallExpr*> cBufferOverflow::GetInput() {
	return m_input;
}

void cBufferOverflow::SetInput(cCodePropertyGraph& cpg) {
	//TODO Traverse cppg in order to find all input nodes.

	clang::CFG& CFG = const_cast<clang::CFG&>(cpg.GetCFG());

	//GetBuffer()->dump();

	//cppg.GetAST().dump();

	cFindInputNodes finder(GetBuffer(), CFG);

	//CFG.dump(clang::LangOptions(), false);
	CFG.VisitBlockStmts(finder);

	m_input = finder.GetInput();

}
