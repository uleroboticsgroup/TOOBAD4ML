#include "description/SinkClassification.h"
#include "description/BufferOverflow.h"
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cSinkClassification::cSinkClassification(IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};


// INHERITED METHODS
// ----------------------------------------------------------------------------

std::string cSinkClassification::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
			cDescriptorDecorator::ExtractFeature(cpg, bof);

	std::string feature = "-1";
	
	if (bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
		feature = "7";
	} else if (bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass){
		
		std::map<std::string, std::string> sinkTypes = {
			// String copy 
			{ "strcpy", "1" }, { "strncpy", "1" },
			// String concatenation 
			{ "strcat", "2" }, { "strncat", "2" },
			// Memory alteration
			{ "memcpy", "3" }, { "memmove", "3" },
			// Formatted string output
			{ "sprintf", "4" }, { "snprintf", "4" },
			// Unformatted string input
			{ "gets", "5" }, { "fgets", "5" },
			// Formatted string input
			{ "scanf", "6" },{ "sscanf", "6" }
		};

		clang::CallExpr* sinkCallExpr = llvm::dyn_cast<clang::CallExpr>(bof.GetSink());

		std::map<std::string, std::string>::iterator sinkTypesIt = sinkTypes.find(sinkCallExpr->getDirectCallee()->getName());

		if(sinkTypesIt != sinkTypes.end()) {
			feature = sinkTypesIt->second;
		}

	}

	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
