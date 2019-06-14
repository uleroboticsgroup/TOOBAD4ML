#ifndef SRC_AST_TRAVERSAL_EXTRACT_VULNERABILITIES_VISITOR_H
#define SRC_AST_TRAVERSAL_EXTRACT_VULNERABILITIES_VISITOR_H

#include <clang/AST/RecursiveASTVisitor.h>

namespace TOOBAD4ML {

namespace ASTTraversal {

/*!
 * A vector of SourceLocation pairs.
 * First sourcelocation pair includes start line and start offset of vulnerability.
 * Second sourcelocation pair includes end line and end offset of vulnerability.
 */

typedef std::pair<clang::SourceLocation, clang::SourceLocation> BOFLocation;

/*!
 * A pair of a FunctionDecl and all the vulnerable nodes within it. The vulnerable
 * nodes are of Expr type.
 */
typedef std::pair<clang::FunctionDecl*, std::vector<clang::Expr*>> BOFNodesPerFunction;

/*!
 * A map of all FunctionDecl and all the vulnerable nodes within each of them.
 */
typedef std::map<clang::FunctionDecl*, std::vector<clang::Expr*>> BOFNodesPerFunctionMap;

/*!
 * This class traverses the provided sourcefile seeking for vulnerability comments,
 * translate those comments into sourcelocation pairs and, finally, converts them into
 * actual AST nodes.
 */
class cExtractVulnerabilitiesVisitor: public clang::RecursiveASTVisitor<
		cExtractVulnerabilitiesVisitor> {

public:

	/*!
	 * As soon as an instance of this class is made, it will call internal extractComments
	 * function in order to traverse the source file provided seeking for vulnerable lines
	 * comments previously written by SonarCloud python bot.
	 * @param ASTContext. The context including source file and AST nodes.
	 */
	cExtractVulnerabilitiesVisitor(clang::ASTContext&);

	/*!
	 *	Getter
	 * @return A map between the vulnerable function (FunctionDecl) and a vector
	 * of all its vulnerable nodes vector<clang::Expr*>
	 */
	BOFNodesPerFunctionMap GetVulnerabilities();

	/*!
	 *
	 * @param Function declaration or definition to traverse.
	 * @return False is there are no vulnerabilities for that sourcefile,
	 * otherwise true.
	 */
	bool VisitFunctionDecl(clang::FunctionDecl*);

	friend class cExtractVulnerabilitiesVisitorTest;
private:

	//!
	std::vector<BOFLocation> m_vulnerableLines;

	//!
	BOFNodesPerFunctionMap m_vulnerabilities;

}; /* class cExtractVulnerabilitiesVisitor */

class cExtractVulnerabilitiesVisitorTest {
public:
	std::vector<BOFLocation> getVulnerableLines(cExtractVulnerabilitiesVisitor &visitor);
};

} /* namespace ASTTraversal */

} /* namespace TOOBAD4ML */

#endif /* SRC_AST_TRAVERSAL_EXTRACT_VULNERABILITIES_VISITOR_H_ */
