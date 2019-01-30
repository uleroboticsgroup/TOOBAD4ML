#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "ASTTraversal/FindSelectedASTNodesVisitor.h"

using namespace TOOBAD4ML;
using namespace ASTTraversal;

/*!
 *	Retrieves all comments from sourcefile and iterate through them in reverse
 *	order, from last to first, until it finds the comment delimiter. For each
 *	found comment, transforms it into a SourceLocation instance.
 * @param context containing source file.
 * @return A BOFLocation vector.
 */
std::vector<BOFLocation> extractComments(clang::ASTContext& context) {
	std::vector<BOFLocation> vulnerableLines;

	llvm::ArrayRef<clang::RawComment*> comments =
			context.getRawCommentList().getComments();
	const char* COMMENT_DELIMITER = "###BEGIN_VULNERABLE_LINES###";
	const llvm::StringRef ELEMENT_SEPARATOR = ";";
	const llvm::StringRef LINECOL_SEPARATOR = ",";
	clang::FileID mainFID = context.getSourceManager().getMainFileID();

	// Reverse iteration through the comments until COMMENT_DELIMETER
	for (llvm::ArrayRef<clang::RawComment*>::iterator it = (comments.end() - 1);
			!comments.empty()
					&& (strcmp((*it)->getBriefText(context), COMMENT_DELIMITER)
							!= 0); it--) {

		llvm::StringRef commentLine((*it)->getBriefText(context));

		std::pair<llvm::StringRef, llvm::StringRef> unparsedElement =
				commentLine.split(ELEMENT_SEPARATOR);

		std::pair<llvm::StringRef, llvm::StringRef> unparsedStartElement =
				unparsedElement.first.split(LINECOL_SEPARATOR);

		std::pair<llvm::StringRef, llvm::StringRef> unparsedEndElement =
				unparsedElement.second.split(LINECOL_SEPARATOR);

		// When unsigned modifier is used by itself, a data type of int is
		// assumed
		unsigned startLine, startCol, endLine, endCol;
		unparsedStartElement.first.getAsInteger(0, startLine);
		unparsedStartElement.second.getAsInteger(0, startCol);
		unparsedEndElement.first.getAsInteger(0, endLine);
		unparsedEndElement.second.getAsInteger(0, endCol);

		BOFLocation parsedLine(
				context.getSourceManager().translateLineCol(mainFID, startLine,
						startCol),
				context.getSourceManager().translateLineCol(mainFID, endLine,
						endCol));

		vulnerableLines.push_back(parsedLine);

	}

	return vulnerableLines;

}


cExtractVulnerabilitiesVisitor::cExtractVulnerabilitiesVisitor(
		clang::ASTContext& context) :
		m_vulnerableLines(extractComments(context)) {
}


BOFNodesPerFunctionMap cExtractVulnerabilitiesVisitor::GetVulnerabilities() {
	return m_vulnerabilities;
}


bool cExtractVulnerabilitiesVisitor::VisitFunctionDecl(
		clang::FunctionDecl* funcDecl) {

	clang::SourceManager& sourceManager =
			funcDecl->getASTContext().getSourceManager();

	// Discard header files
	if (!m_vulnerableLines.empty()
			&& sourceManager.isInMainFile(funcDecl->getLocStart())) {
		/*
		 * After checking there are indeed vulnerable lines for the actual sourcefile
		 * and it is not a header file, another visitor is invoked in order to
		 * transform those SourceLocation into actual AST Nodes of Expr type.
		 */
		// Extract the AST node of the given vulnerable lines
		cFindSelectedASTNodesVisitor finder(m_vulnerableLines);
		finder.TraverseDecl(funcDecl);

		std::vector<clang::Expr*> selectedNodes = finder.GetSelectedNodes();

		/*
		 * If there are indeed vulnerable nodes, we create a new BOFNodesPerFunction
		 * and insert it into m_vulnerabilities.
		 */
		if (!selectedNodes.empty()) {
			m_vulnerabilities.insert(
					BOFNodesPerFunction(funcDecl, selectedNodes));
		}

	}

	return m_vulnerableLines.empty() ? false : true;
}
