#include "description/BufferOverflowBuilder.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "ASTTraversal/FindVariableVisitor.h"

using namespace TOOBAD4ML;
using namespace description;

typedef std::pair<int, int> BufferArgIndices; 

cBufferOverflow& cBufferOverflowBuilder::CreateBufferOverflow(clang::Expr& sink, cCodePropertyGraph& cpg) {
    clang::DeclRefExpr* dstBuffer = getBuffer(sink, BufferType::DST);
	clang::DeclRefExpr* srcBuffer = getBuffer(sink, BufferType::SRC);

	//clang::LangOptions options;
	//cpg.GetCFG().dump(options, true);

	std::vector<clang::Expr*> sinkSanitizations = getSinkSanitizations(dstBuffer, srcBuffer,cpg.GetSPG(sink));

    std::vector<clang::CallExpr*> inputs = getInputs(*dstBuffer, cpg.GetSPG(sink));
    return *(new cBufferOverflow(&sink, dstBuffer, srcBuffer, inputs, sinkSanitizations));
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

			default: {
				//TODO binary operator class -- find cases.
			}
            break;
		}
    }

	return inputs;
}

clang::DeclRefExpr* cBufferOverflowBuilder::getBuffer(clang::Expr& sink, BufferType bufferType) {
		clang::DeclRefExpr* buffer = nullptr;
    	switch (sink.getStmtClass()) {

		case clang::Stmt::StmtClass::CallExprClass: {
			clang::CallExpr* sinkCallExpr = llvm::dyn_cast_or_null<clang::CallExpr>(&sink);

			if (sinkCallExpr) {
				// map {sink Type, buffer argument indices(dst, src)}
				std::map<std::string, BufferArgIndices> sinkTypes = {
					{ "strcpy", BufferArgIndices(0, 1) }, { "strncpy", BufferArgIndices(0, 1) },
					{ "strcat", BufferArgIndices(0, 1) }, { "strncat", BufferArgIndices(0, 1) },
					{ "memcpy", BufferArgIndices(0, 1) }, { "memmove", BufferArgIndices(0, 1) },
					{ "sprintf", BufferArgIndices(0, -1) }, { "snprintf", BufferArgIndices(0, -1) },
					{ "gets", BufferArgIndices(0, -1) }, { "fgets", BufferArgIndices(0, -1) },
					{ "scanf", BufferArgIndices(1, -1) },{ "sscanf", BufferArgIndices(0, -1) }, };

				std::string functionName = sinkCallExpr->getDirectCallee()->getNameAsString();

				// Get the buffer's AST node by searching its position inside the arguments list of the sink node.
				std::map<std::string, BufferArgIndices>::iterator argSignatureIt = sinkTypes.find(functionName);
				if(argSignatureIt != sinkTypes.end()) {
					bool argIndex = bufferType == BufferType::SRC ? 1 : 0;
					int index = argIndex ? argSignatureIt->second.second : argSignatureIt->second.first;
					
					if (index == -1) break;

					clang::Expr* bufferExpr = sinkCallExpr->getArg(index)->IgnoreCasts();
					
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
				clang::Expr* bufferExpr = (bufferType == BufferType::DST) ? sinkBinaryOperator->getLHS() : sinkBinaryOperator->getRHS() ;
				switch(bufferExpr->getStmtClass()) {
					case clang::Stmt::StmtClass::ArraySubscriptExprClass: {
						// The buffer is the base of the the sink node's left handed side expression.
						buffer = llvm::dyn_cast<clang::DeclRefExpr>(llvm::dyn_cast<clang::ArraySubscriptExpr>(bufferExpr)->getBase()->IgnoreCasts());
					}
					break;
					default: { // TODO Not default -- Use the concrete class
						// TODO *(p + n) = 0; -- UnaryOperatorClass ??
					}
					break;
				}
			}
		}
	}

	return buffer;
}

/* 
bool isBufferInside(clang::Expr* sideExpr, clang::DeclRefExpr* buffer) {
	switch	(sideExpr->getStmtClass()) {
		case clang::Stmt::StmtClass::UnaryOperatorClass: {
			clang::UnaryOperator* unaryOperator = llvm::dyn_cast<clang::UnaryOperator>(sideExpr);
			return isBufferInside(unaryOperator->getSubExpr(), buffer);
		}
		break;

		case clang::Stmt::StmtClass::DeclRefExprClass: {
			clang::DeclRefExpr* declRefExpr = llvm::dyn_cast<clang::DeclRefExpr>(sideExpr);

			return declRefExpr->getDecl() == buffer->getDecl();
		}
		break;

		case clang::Stmt::StmtClass::UnaryExprOrTypeTraitExprClass: {
			clang::UnaryExprOrTypeTraitExpr* unaryExprOrTypeTraitExpr = llvm::dyn_cast<clang::UnaryExprOrTypeTraitExpr>(sideExpr);

			return isBufferInside(unaryExprOrTypeTraitExpr->getArgumentExpr()->IgnoreParens(), buffer);
		}
		break;

		case clang::Stmt::StmtClass::CallExprClass: {
			clang::CallExpr* callExpr = llvm::dyn_cast<clang::CallExpr>(sideExpr);
			bool found = false;

			for(int i = 0; i < callExpr->getNumArgs(); i++) {
				found = found | isBufferInside(callExpr->getArg(i), buffer);
			}

			return found;
		}
		break;
		default:
			return false;

		//TODO Other cases ?.
	}
}
*/
 
std::vector<clang::Expr*> cBufferOverflowBuilder::getSinkSanitizations(clang::DeclRefExpr* dstBuffer, clang::DeclRefExpr* srcBuffer, SinkPathGraph spg) {
	std::vector<clang::Expr*> sanitizations;

	for(clang::CFGStmt cfgStmt: spg)  {
		clang::Stmt* stmt = const_cast<clang::Stmt*>(cfgStmt.getStmt());
		switch	(stmt->getStmtClass()) {
			case clang::Stmt::StmtClass::BinaryOperatorClass: {
				clang::BinaryOperator* conditionBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(stmt);

				ASTTraversal::cFindVariableVisitor dstVisitor(dstBuffer);
				dstVisitor.TraverseStmt(stmt);
				ASTTraversal::cFindVariableVisitor srcVisitor(srcBuffer);
				srcVisitor.TraverseStmt(stmt);

				if (dstVisitor.IsFound() || srcVisitor.IsFound()) {
					sanitizations.push_back(conditionBinaryOperator);
				}
			}
			break;
			//TODO Other cases switchCase // callExpr ?.
		}
	}

	return sanitizations;
}

