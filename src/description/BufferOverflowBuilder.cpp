#include "description/BufferOverflowBuilder.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "iostream"
#include "ASTTraversal/FindVariableVisitor.h"

using namespace TOOBAD4ML;
using namespace description;

cBufferOverflow& cBufferOverflowBuilder::CreateBufferOverflow(clang::Expr& sink, cCodePropertyGraph& cpg) {
    clang::DeclRefExpr* buffer = getBuffer(sink);
    std::vector<clang::CallExpr*> inputs = getInputs(*buffer, cpg.GetSPG(sink));
    return *(new cBufferOverflow(&sink, buffer, inputs));
}

std::vector<clang::CallExpr*> cBufferOverflowBuilder::getInputs(clang::DeclRefExpr& buffer, SinkPathGraph spg) {
    std::vector<clang::CallExpr*> inputs;

    for(clang::CFGStmt cfgStmt: spg)  {
        clang::Stmt* aux = const_cast<clang::Stmt*>(cfgStmt.getStmt());

		switch (aux->getStmtClass()) {

			case clang::Stmt::StmtClass::CallExprClass: {

				ASTTraversal::cFindVariableVisitor visitor(&buffer);
				visitor.TraverseStmt(aux);
				if (visitor.IsFound()) {
					if(clang::CallExpr* call = llvm::cast<clang::CallExpr>(aux)){
						inputs.push_back(call);
					}
				}

			}

			break;

			case clang::Stmt::StmtClass::BinaryOperatorClass: { /*
			 if(inputClassificationtypes.find(llvm::cast<clang::CallExpr>(aux)->getDirectCallee()->getNameAsString()) != inputClassificationtypes.end()){
			 ASTTraversal::cFindVariableVisitor m_visitor(sink);
			 m_visitor.TraverseStmt(const_cast<clang::Stmt*>(aux));

			 if (m_visitor.isFound()) {
			 //TODO Get right handed side of binaryoperator
			 //m_input.push_back(llvm::cast<clang::CallExpr>(aux));
			 }
			 }*/
			}
            break;
		}
    }

	return inputs;
}

clang::DeclRefExpr* cBufferOverflowBuilder::getBuffer(clang::Expr& sink) {
    	switch (sink.getStmtClass()) {

		case clang::Stmt::StmtClass::CallExprClass: {

			clang::CallExpr* call = llvm::dyn_cast_or_null<clang::CallExpr>(&sink);

			// map {sink Type, buffer position}
			std::map<std::string, int> sinkTypes = {
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
										return ref;
									} else {
										llvm::outs() << "El buffer no es de typo array\n";
									}

								}

							} else if(nameExpr.compare("MemberExpr") == 0) { 
                                //TODO Buffer for structs, unions
								// buff->dumpColor();
								//return ref;
							}
						}
					}
				}
			}

		}

		break;

		case clang::Stmt::StmtClass::BinaryOperatorClass: {

			if(clang::BinaryOperator* binaryOperator = llvm::dyn_cast<clang::BinaryOperator>(&sink)) {

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
											return ref;
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