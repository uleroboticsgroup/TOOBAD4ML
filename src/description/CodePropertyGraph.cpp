#include "description/CodePropertyGraph.h"
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;
// ----------------------------------------------------------------------------

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cCodePropertyGraph::cCodePropertyGraph(clang::FunctionDecl& functionDecl)
    : m_AST(functionDecl) {

    // prevent building the CFG of undefined functions
    assert(m_AST.doesThisDeclarationHaveABody() == true);
    m_CFG = clang::CFG::buildCFG(&m_AST, m_AST.getBody(),
				&m_AST.getASTContext(), clang::CFG::BuildOptions());
}

cCodePropertyGraph::~cCodePropertyGraph() {
    m_CFG.reset();
    // clang will take care of freeing the AST reference
}


// ACCESSOR METHODS
// ----------------------------------------------------------------------------

const clang::FunctionDecl& cCodePropertyGraph::GetAST() {
	return m_AST;
}

const clang::CFG& cCodePropertyGraph::GetCFG(){
	return *m_CFG;
}
