#include "description/CodePseudoPropertyGraph.h"

using namespace TOOBAD4ML;
using namespace description;


cCodePseudoPropertyGraph::cCodePseudoPropertyGraph(
		clang::FunctionDecl& functionDecl) :
		m_AST(functionDecl) {

	if (m_AST.doesThisDeclarationHaveABody()) {
		m_CFG = clang::CFG::buildCFG(&m_AST, m_AST.getBody(),
				&m_AST.getASTContext(), clang::CFG::BuildOptions());
	}

}

const clang::CFG& cCodePseudoPropertyGraph::GetCFG(){
	return *m_CFG;
}

clang::FunctionDecl& cCodePseudoPropertyGraph::GetAST() {
	return m_AST;
}
