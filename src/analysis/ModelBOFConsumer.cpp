#include "analysis/ModelBOFConsumer.h"
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
#include "description/PadmanabhuniBuilder.h"
#include "description/CPGExplorer.h"
#include "description/CodePropertyGraph.h"
#include "description/BufferOverflow.h"

using namespace TOOBAD4ML;
using namespace analysis;


cModelBOFConsumer::cModelBOFConsumer(clang::ASTContext* context) {
}

void cModelBOFConsumer::HandleTranslationUnit(clang::ASTContext& context) {

	/**
	 * That's the visitor that traverses the source file seeking for
	 * comments previously written by SonarCloud python bot.
	 */
	// extract all the vulnerabilities from the Translation Unit
	ASTTraversal::cExtractVulnerabilitiesVisitor visitor(context);
	visitor.TraverseDecl(context.getTranslationUnitDecl());

	ASTTraversal::BOFNodesPerFunctionMap vulnerabilities =
			visitor.GetVulnerabilities();

	// ############################# //

	// iterate through the vulnerabilities to extract the descriptors
	description::cPadmanabhuniBuilder pmd;
	description::cCPGExplorer explorer(pmd.CreateDescriptor());

	for (ASTTraversal::BOFNodesPerFunctionMap::iterator iterFunction =
			vulnerabilities.begin(); iterFunction != vulnerabilities.end();
			iterFunction++) {
		/**
		 * For each function within BOFNodesPerFunctionMap we declare
		 * a new CodePropertyGraph.
		 */
        description::cCodePropertyGraph cpg(*(iterFunction->first));

		// use the CPG to extract the vulnerabilities
        int count = 0;
		for (std::vector<clang::Expr*>::iterator iterBOF =
				iterFunction->second.begin();
				iterBOF != iterFunction->second.end(); iterBOF++) {

			count = count +1;
			llvm::outs() << "SINK N " << count << " .\n";

			//TODO: Documentation from here: Documenting BUFFEROVERFLOW class
			// and its implementation is yet undone.

            description::cBufferOverflow BOF(**iterBOF);
			BOF.SetInput(cpg);

			std::string features= explorer.Inspect(cpg, BOF);
			m_dataset.push_back(features);
		}
	}

	for (std::vector<std::string>::iterator it = m_dataset.begin(); it != m_dataset.end(); ++it) {

		llvm::outs() << "Dataset: " << *it << "\n";
	}

}
