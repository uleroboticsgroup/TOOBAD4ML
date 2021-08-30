#include "ASTTraversal/FindSelectedASTNodesVisitor.h"
#include <iostream>

using namespace TOOBAD4ML;
using namespace ASTTraversal;

cFindSelectedASTNodesVisitor::cFindSelectedASTNodesVisitor(
	std::vector<BOFLocation> &lines) : m_vulnerableLines(lines)
{
}

std::vector<clang::Expr *> cFindSelectedASTNodesVisitor::GetSelectedNodes()
{
	return m_selectedNodes;
}

bool cFindSelectedASTNodesVisitor::VisitCallExpr(clang::CallExpr *callExpr)
{
	return isVulnerable(callExpr);
}

bool cFindSelectedASTNodesVisitor::VisitBinaryOperator(
	clang::BinaryOperator *binaryOperator)
{
	return isVulnerable(binaryOperator);
}

bool cFindSelectedASTNodesVisitor::isVulnerable(clang::Expr *expr)
{
	for (std::vector<BOFLocation>::iterator it = m_vulnerableLines.begin();
		 (!m_vulnerableLines.empty()) && (it != m_vulnerableLines.end());)
	{
		// TODO: https://clang.llvm.org/doxygen/classclang_1_1FullSourceLoc.html
		//
		//llvm::outs() << "LocStart (offset)" << expr->getLocStart().getFileOffset();
		//llvm::outs() << "LocEnd (offset)" << expr->getLocEnd().getFileOffset();

		if ((it->first == expr->getLocStart() && it->second == expr->getLocEnd()))
		{
			m_selectedNodes.push_back(expr);
			it = m_vulnerableLines.erase(it);

			//llvm::outs() << "Node is:" << expr->getStmtClassName() << "\n";
			//expr->dumpColor();
		}
		else
		{
			it++;
		};
	}

	return m_vulnerableLines.empty() ? false : true;
}