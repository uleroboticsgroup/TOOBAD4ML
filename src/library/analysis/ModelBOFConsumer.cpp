// -----------------------------------------------------------------------------
#include "analysis/ModelBOFConsumer.h"
// -----------------------------------------------------------------------------
#include "description/Descriptor.h"
#include "description/CPGExplorer.h"
#include "description/CodePropertyGraph.h"
#include "description/BufferOverflow.h"
#include "description/BufferOverflowBuilder.h"
// -----------------------------------------------------------------------------
#include "ASTTraversal/ExtractVulnerabilitiesVisitor.h"
// -----------------------------------------------------------------------------
#include "io/FileManager.h"
#include "io/CmdLineArguments.h"
#include "io/Logger.h"
// -----------------------------------------------------------------------------
#include <iostream>
#include "clang/Lex/Lexer.h"
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
    IO::cLogger* logger = IO::cLogger::GetInstance();
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
        
        logger->Write(IO::eLogLevel::INFO, "Vulnerabilities found: " + std::to_string(functionIter.second.size()));

        for (auto const& vulnLOCIter : functionIter.second) {
            logger->Write(IO::eLogLevel::DEBUG, "Analyzing vulnerable expression: " + clang::Lexer::getSourceText(clang::CharSourceRange((*vulnLOCIter).getSourceRange(), true), context.getSourceManager(), context.getLangOpts()).str());
            std::cout << ".";
            // encapsulate the data related to the current vulnerable LOC
            description::cBufferOverflowBuilder BOFBuilder;
            description::cBufferOverflow BOF = BOFBuilder.CreateBufferOverflow(*vulnLOCIter, cpg);
            // and finally use the previous elements to start the analysis and
            // store the corresponding result
			std::string descriptor = m_CPGExplorer.Inspect(cpg, BOF);
            logger->Write(IO::eLogLevel::INFO, "Descriptor: " + descriptor);
			m_dataset.push_back(descriptor);
		}
	}

    std::cout << " Completed" << "\n";
}

// CLASS METHODS
// -------------------------------------------------------------------------

bool cModelBOFConsumer::Output(IO::sCmdLineArguments& args) {
    IO::cLogger* logger = IO::cLogger::GetInstance();
    IO::cFileManager *fm = IO::cFileManager::GetInstance();
    IO::cFileManager fileManager = *fm;

    bool success = fileManager.Write(m_dataset, args.getStrategy(), args.getFilename(), args.getAppend()); 
    logger->Write(IO::eLogLevel::INFO, "Writing output. Result: " + std::string(success ? "success" : "failure"));

    if (!success) {
        std::cout << "An error occurred while writing the results." <<  "\n";
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