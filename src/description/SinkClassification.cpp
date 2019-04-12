#include "description/SinkClassification.h"
#include "description/BufferOverflow.h"
#include "ASTTraversal/FindFunctionVisitor.h"

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

	std::map<llvm::StringRef, llvm::StringRef> sinkTypes = {
			{ "strcpy", "1" }, { "strncpy", "1" },
			{ "strcat", "2" }, { "strncat", "2" },
			{ "memcpy", "3" }, { "memmove", "3" },
			{ "sprintf", "4" }, { "snprintf", "4" },
			{ "gets", "5" }, { "fgets", "5" },
			{ "scanf", "6" },{ "sscanf", "6" }, };

	std::string feature;

	//TODO Get rid of magic literals string to actual constants
	if (bof.GetSinkType() == clang::Stmt::StmtClass::BinaryOperatorClass) {
		feature = "7";
	} else {

		ASTTraversal::cFindFunctionVisitor fun(bof.GetSink());
		fun.TraverseStmt(bof.GetSink());

		if(sinkTypes.find(fun.getFunctionName()) == sinkTypes.end()) {
			llvm::outs() << "No function found in sink types." << "\n";
			feature = "0";
		} else {
			feature = sinkTypes.find(fun.getFunctionName())->second;
		}

	}

	llvm::outs() << "SinkClassification: " <<  feature << "\n";
	//return decoratedFeature.append("SinkClassification: ");
	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
