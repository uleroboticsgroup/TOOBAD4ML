#ifndef  SRC_CORE_CODE_PSEUDO_PROPERTY_GRAPH_H_
#define  SRC_CORE_CODE_PSEUDO_PROPERTY_GRAPH_H_

#include <clang/AST/Decl.h>
#include <clang/Analysis/CFG.h>

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTContext.h>

namespace TOOBAD4ML {

namespace description {

/*!
 * This class represent the CodePseudoPropertyGraph the tool uses
 * for creating vulnerabilities descriptors.
 */
class cCodePseudoPropertyGraph {
public:

	/*!
	 * Constructor of CodePseudoPropertyGraph. It checks whether the
	 * received parameter (FunctionDecl) has body. If it does, it then
	 * constructs the corresponding CFG.
	 *
	 * @param FunctionDecl from BOFNodesPerFunctionMap
	 */
	cCodePseudoPropertyGraph(clang::FunctionDecl&);

	const clang::CFG& GetCFG();

	clang::FunctionDecl& GetAST();

private:

	//! Internal copy of the constructor parameter FunctionDecl
	clang::FunctionDecl& m_AST;

	//! Control Flow Graph generated from m_AST
	std::unique_ptr<clang::CFG> m_CFG;

};
/* cCodePseudoPropertyGraph */

} /* namespace description */

} /* namespace TOOBAD4ML */

#endif /*  SRC_CORE_CODE_PSEUDO_PROPERTY_GRAPH_H_ */
