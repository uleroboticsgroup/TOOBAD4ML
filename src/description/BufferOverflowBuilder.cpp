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
		clang::DeclRefExpr* buffer = nullptr;
    	switch (sink.getStmtClass()) {

		case clang::Stmt::StmtClass::CallExprClass: {
			clang::CallExpr* sinkCallExpr = llvm::dyn_cast_or_null<clang::CallExpr>(&sink);

			if (sinkCallExpr) {
				// map {sink Type, buffer position}
				std::map<std::string, int> sinkTypes = {
					{ "strcpy", 0 }, { "strncpy", 0 },
					{ "strcat", 0 }, { "strncat", 0 },
					{ "memcpy", 0 }, { "memmove", 0 },
					{ "sprintf", 0 }, { "snprintf", 0 },
					{ "gets", 0 }, { "fgets", 0 },
					{ "scanf", 1 },{ "sscanf", 0 }, };

				std::string functionName = sinkCallExpr->getDirectCallee()->getNameAsString();

				// Get the buffer's AST node by searching its position inside the arguments list of the sink node.
				std::map<std::string, int>::iterator argSignatureIt = sinkTypes.find(functionName);
				if(argSignatureIt != sinkTypes.end()) {
					clang::Expr* bufferExpr = sinkCallExpr->getArg(argSignatureIt->second)->IgnoreCasts();
					if(bufferExpr) {
						// Check the type of the buffer
						switch (bufferExpr->getStmtClass()) {
							case clang::Stmt::StmtClass::DeclRefExprClass: {
								if (bufferExpr->getType().getTypePtr()->isArrayType()) {
									buffer = llvm::dyn_cast<clang::DeclRefExpr>(bufferExpr);
								}
							}
							break;
							default: {
								//TODO Buffer for structs, unions (MemberExprClass)
							}
							break;

						}
					}
				}
			}

		}

		break;

		case clang::Stmt::StmtClass::BinaryOperatorClass: {
			clang::BinaryOperator* sinkBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(&sink);
			if(sinkBinaryOperator) {
				clang::Expr* bufferExpr = sinkBinaryOperator->getLHS();
				switch(bufferExpr->getStmtClass()) {
					case clang::Stmt::StmtClass::ArraySubscriptExprClass: {
						// The buffer is the base of the the sink node's left handed side expression.
						buffer = llvm::dyn_cast<clang::DeclRefExpr>(llvm::dyn_cast<clang::ArraySubscriptExpr>(bufferExpr)->getBase()->IgnoreCasts()); 
					}
					break;
					default: {
						// TODO *(p + n) = 0; -- UnaryOperatorClass ??
					}
					break;
				}
			}
		}
	}

	return buffer;
}