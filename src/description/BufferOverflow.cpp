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


//TODO: move this class out of this file.
/*!
 * This class is called with CFG.VisitBlockStmts. That is,
 * given a CFG, clang will internally call this class each time
 * it traverses a basic block, for each statement.
 */
class cFindInputNodes {
public:

	cFindInputNodes(clang::DeclRefExpr* declRef, clang::CFG& CFG) :
			m_buffer(declRef), m_cfg(CFG) {
	}

	void operator()(const clang::Stmt* stmt) {

		clang::Stmt* aux = const_cast<clang::Stmt*>(stmt);
		switch (aux->getStmtClass()) {

		case clang::Stmt::StmtClass::CallExprClass: {

			ASTTraversal::cFindVariableVisitor m_visitor(m_buffer);

			llvm::outs() << "IMPRIMIENDO DESDE CFINDINPUTNODES.\n";
			m_buffer->dumpColor();

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

	clang::DeclRefExpr* m_buffer;
	std::vector<clang::CallExpr*> m_input;
	clang::CFG& m_cfg;

};


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cBufferOverflow::cBufferOverflow(clang::Expr& sink) :
		m_sink(&sink), m_buffer(0) {

	//llvm::outs() << "Printing from cBufferOverflow constructor.\n";
	//m_sink->dumpColor();

	//TODO: aQUI ES DONDE DA PORBLEMAS PORQUE BUFFER NUNCA SE ASIGNA.
	//SE DEBE CAMBIAR LA MODADLIDA DE DOBLE FOR A LA IMPLEMENTACIÓN
	//DE UN VISITOR

	// TODO: change ifs for switch
	// PENDIENTE IMPLEMENTAR!!!!!!!!!!!!!!!!!

//	if (GetSinkType() == clang::Stmt::StmtClass::CallExprClass) {
//		llvm::outs() << "Printing from CallExprClass.\n";
//		clang::CallExpr *callExpr = llvm::dyn_cast<clang::CallExpr>(m_sink);
//
////		unsigned count = 0;
////		//llvm::iterator_range<clang::Stmt::child_range> rango = callExpr->children();
////		clang::Stmt::child_range rango = callExpr->children();
////		for (clang::Stmt::child_iterator it = rango.begin(); it != rango.end();
////				it++) {
////			count++;
////		}
//
//		//for (clang::Stmt::child_range it = callExpr->child_begin(); it != callExpr->child_end(); it++) {
////		for (clang::Stmt::child_iterator it = callExpr->child_begin(); it != callExpr->child_end(); ++it) {
////			count++;
////		}
////
//		//llvm::outs() << count << "\n";
//
//		for (clang::Stmt::child_iterator it = callExpr->child_begin();
//				(!m_buffer) && (it != callExpr->child_end()); it++) {
//
//			for (clang::Stmt::child_iterator it2 = (*it)->child_begin();
//					(!m_buffer) && (it2 != (*it)->child_end()); it2++) {
//
//				if ((*it2)->getStmtClass()
//						== clang::Stmt::StmtClass::DeclRefExprClass) {
//
//					clang::DeclRefExpr *decl =
//							llvm::dyn_cast<clang::DeclRefExpr>(*it2);
//
//					if (clang::ValueDecl* var = decl->getDecl()) {
//
//						if (var->getKind() == clang::Decl::Var) {
//							llvm::outs() << "Delc desde buffer.\n";
//							m_buffer = decl;
//							break;
//						}
//					}
//				}
//			}
//		}
//
//	} else if (GetSinkType() == clang::Stmt::StmtClass::BinaryOperatorClass) {
//
//		llvm::outs() << "Printing from BinaryOperatorClass.\n";
//		clang::BinaryOperator* binOP = llvm::dyn_cast<clang::BinaryOperator>(
//				m_sink);
//
//		clang::Expr* LHS = binOP->getLHS();
//		llvm::outs() << "DUMPING FROM BINARY WOW MAN, KEWL!!!!.\n";
//		LHS->dumpColor();
//		if (binOP->getOpcode() == clang::BO_Assign) {
//
//			for (clang::Stmt::child_iterator it = LHS->child_begin();
//					(!m_buffer) && (it != LHS->child_end()); it++) {
//				if ((*it)->getStmtClass()
//						== clang::Stmt::StmtClass::ImplicitCastExprClass) {
//					for (clang::Stmt::child_iterator it2 = (*it)->child_begin();
//							it2 != (*it)->child_end(); it2++) {
//						if ((*it2)->getStmtClass()
//								== clang::Stmt::StmtClass::DeclRefExprClass) {
//							m_buffer = llvm::dyn_cast<clang::DeclRefExpr>(*it2);
//							break;
//						}
//					}
//				}
//			}
//		}
//
//	}
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

clang::DeclRefExpr* cBufferOverflow::GetBuffer() {
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
