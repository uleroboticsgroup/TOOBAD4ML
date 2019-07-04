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
#include "io/FileManager.h"
#include "io/CSVOutputFormatStrategy.h"
#include "io/STDOutputFormatStrategy.h"

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

			m_dataset.push_back(descriptor);
		}
	}
    std::cout << "ANALYZED" << "\n";
}

// CLASS METHODS
// -------------------------------------------------------------------------

bool cModelBOFConsumer::Output(TOOBAD4ML::IO::IOutputFormatStrategy& strategy, const llvm::Twine& filename = "") {
    IO::cFileManager *fm = IO::cFileManager::GetInstance();
    std::cout << "ALL GOOD" << "\n";
    std::cout << filename.str() << "\n";
    IO::cFileManager fileManager = *fm;
    std::cout << "ALL GOOD" << "\n";

    bool success = fileManager.Write(m_dataset, &strategy, filename, false); 

    if (!success) {
        std::cout << "An error occurred while writing the results." <<  "\n";
    }
    else{
        std::cout << "Results have been written." << "\n";   
    }

    return success;
}

// ACCESSOR METHODS
// -------------------------------------------------------------------------

void cModelBOFConsumer::SetModel(description::IDescriptor& model) {
    m_CPGExplorer.SetDescriptor(model);
}

std::vector<std::string> cModelBOFConsumerTest::getDataset(cModelBOFConsumer& consumer) {
	return consumer.m_dataset;
}
