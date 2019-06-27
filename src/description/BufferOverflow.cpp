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

	cFindInputNodes(clang::Expr* declRef, clang::CFG& CFG) :
			m_buffer(declRef), m_cfg(CFG) {
	}

	void operator()(const clang::Stmt* stmt) {

		clang::Stmt* aux = const_cast<clang::Stmt*>(stmt);

//		llvm::outs() << "dentro OPERATOR\n";
//		aux->dumpColor();

		switch (aux->getStmtClass()) {

			case clang::Stmt::StmtClass::CallExprClass: {

				ASTTraversal::cFindVariableVisitor m_visitor(m_buffer);
				m_visitor.TraverseStmt(aux);
				if (m_visitor.IsFound()) {
					if(clang::CallExpr* call = llvm::cast<clang::CallExpr>(aux)){
						m_input.push_back(call);
					}
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

	// get type of stmt class
	switch (sink.getStmtClass()) {

		case clang::Stmt::StmtClass::CallExprClass: {

			clang::CallExpr* call = llvm::dyn_cast_or_null<clang::CallExpr>(m_sink);

			// map {sink Type, buffer position}
			std::map<llvm::StringRef, int> sinkTypes = {
					{ "strcpy", 0 }, { "strncpy", 0 },
					{ "strcat", 0 }, { "strncat", 0 },
					{ "memcpy", 0 }, { "memmove", 0 },
					{ "sprintf", 0 }, { "snprintf", 0 },
					{ "gets", 0 }, { "fgets", 0 },
					{ "scanf", 1 },{ "sscanf", 0 }, };

			// get function name of sink
			std::string nameFunction;
			if(call==nullptr) {
				// error
			} else {

				nameFunction = call->getDirectCallee()->getNameAsString();

				// if the sink is the above type
				auto it = sinkTypes.find(nameFunction);
				if(it == sinkTypes.end()) {
						llvm::outs() << "No se ha encontrado el sink\n";
				} else {

					int posBufferArg = it->second;

					if(clang::Expr* buff = call->getArg(posBufferArg)->IgnoreCasts()) {

						if(buff != nullptr) {
							std::string nameExpr = buff->getStmtClassName();

							if(nameExpr.compare("DeclRefExpr") == 0) {

								if(clang::DeclRefExpr *ref = llvm::dyn_cast<clang::DeclRefExpr>(buff)) {
									clang::QualType t = buff->getType();

									// if the DeclRefExpr is of type Array
									if(t.getTypePtr()->isArrayType() || t.getTypePtr()->isConstantArrayType()) {
										//buff->dumpColor();
										m_buffer = buff;
									} else {
										llvm::outs() << "El buffer no es de typo array\n";
									}

								}

							} else if(nameExpr.compare("MemberExpr") == 0) { //TODO Buffer for structs, unions
								// buff->dumpColor();
								m_buffer = buff;
							}
						}
					}
				}
			}

		}

		break;

		case clang::Stmt::StmtClass::BinaryOperatorClass: {

			if(clang::BinaryOperator* binaryOperator = llvm::dyn_cast<clang::BinaryOperator>(m_sink)) {

				if(binaryOperator->getLHS()->getStmtClass() == clang::Stmt::StmtClass::ArraySubscriptExprClass) {

					if(clang::ArraySubscriptExpr* arrayExpr =  llvm::dyn_cast<clang::ArraySubscriptExpr>(binaryOperator->getLHS())) {

						if(clang::Expr* buff = arrayExpr->getLHS()->IgnoreCasts()) {

							if(buff != nullptr){
								std::string nameExpr = buff->getStmtClassName();

								if(nameExpr.compare("DeclRefExpr") == 0) {

									if(clang::DeclRefExpr *ref = llvm::dyn_cast<clang::DeclRefExpr>(buff)) {
										clang::QualType t = buff->getType();

										// if the DeclRefExpr is of type Array
										if(t.getTypePtr()->isArrayType()) {
											//buff->dumpColor();
											m_buffer = buff;
										}
									}

								}
							}
						}
					}

				}
			}

		}

	}

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

	cFindInputNodes finder(GetBuffer(), CFG);

	CFG.VisitBlockStmts(finder);

	m_input = finder.GetInput();





//	  for (clang::CFG::const_iterator I=CFG.begin(), E=CFG.end(); I != E; ++I){
//
//		  const clang::CFGBlock *pred = *I;
//
//		  pred->op
//
//		  llvm::outs() <<  pred->getBlockID() << "\n";
//
//	      for (clang::CFGBlock::const_succ_iterator BI=pred->succ_begin(), BE=pred->succ_end();
//	           BI != BE; ++BI) {
//
//	    	  const clang::CFGBlock::AdjacentBlock B = *BI;
//
//
//
//	      }
//	  }
//

}
