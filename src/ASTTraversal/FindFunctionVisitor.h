
#ifndef SRC_ASTTRAVERSAL_FINDFUNCTIONVISITOR_H_
#define SRC_ASTTRAVERSAL_FINDFUNCTIONVISITOR_H_

#include <clang/AST/RecursiveASTVisitor.h>

namespace TOOBAD4ML {

namespace ASTTraversal {

class cFindFunctionVisitor : public clang::RecursiveASTVisitor<cFindFunctionVisitor>{

public:
	cFindFunctionVisitor(clang::Expr *e);

	bool VisitDeclRefExpr(clang::Expr *e);

	std::string getFunctionName();

private:

	clang::DeclRefExpr *m_function;

	std::string m_functionName;

};

} /* namespace ASTTraversal */

} /* namespace TOOBAD4ML */

#endif /* SRC_ASTTRAVERSAL_FINDFUNCTIONVISITOR_H_ */
