// -----------------------------------------------------------------------------
#include "analysis/ModelBOFConsumer.h"
// -----------------------------------------------------------------------------
#include "description/Descriptor.h"
#include "description/CPGExplorer.h"
// -----------------------------------------------------------------------------
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
// -----------------------------------------------------------------------------
#include "description/CodePropertyGraph.h"
#include "description/BufferOverflow.h"
#include <iostream>

// -----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace analysis;
// -----------------------------------------------------------------------------


// CONSTRUCTORS & DESTRUCTORS
// -----------------------------------------------------------------------------

cModelBOFConsumer::cModelBOFConsumer(description::IDescriptor& model)
    : m_CPGExplorer(*(new description::cCPGExplorer(model))) {}


// clang::ASTConsumer INHERITED METHODS
// -----------------------------------------------------------------------------

void cModelBOFConsumer::HandleTranslationUnit(clang::ASTContext& context) {
    // traverse the source's translation unit to extract all tagged lines of
    // code (LOC)
	ASTTraversal::cExtractVulnerabilitiesVisitor visitor(context);
	visitor.TraverseDecl(context.getTranslationUnitDecl());

    // these LOC are arranged per function, so we need to iterate through them
    // in order to start the analysis
    ASTTraversal::BOFNodesPerFunctionMap vulnerabilities =
        visitor.GetVulnerabilities();

    for (auto const& functionIter : vulnerabilities) {
        // we need one CPG per function in order to perform the analysis
        description::cCodePropertyGraph cpg(*(functionIter.first));

        for (auto const& vulnLOCIter : functionIter.second) {
            // encapsulate the data related to the current vulnerable LOC
            description::cBufferOverflow BOF(*vulnLOCIter);
			BOF.SetInput(cpg);

            // and finally use the previous elements to start the analysis and
            // store the corresponding result
			std::string descriptor = m_CPGExplorer.Inspect(cpg, BOF);
		    //std::cout << descriptor << "\n";

			m_dataset.push_back(descriptor);
		}
	}
}


// CLASS METHODS
// -------------------------------------------------------------------------

bool cModelBOFConsumer::Output() {
    // TODO. code this
    return true;
}

// ACCESSOR METHODS
// -------------------------------------------------------------------------

void cModelBOFConsumer::SetModel(description::IDescriptor& model) {
    m_CPGExplorer.SetDescriptor(model);
}

std::vector<std::string> cModelBOFConsumerTest::getDataset(cModelBOFConsumer& consumer) {
	return consumer.m_dataset;
}
