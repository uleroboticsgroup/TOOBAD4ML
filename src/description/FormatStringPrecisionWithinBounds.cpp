#include "description/FormatStringPrecisionWithinBounds.h"
#include "description/BufferOverflow.h"


// ----------------------------------------------------------------------------

using namespace TOOBAD4ML;
using namespace description;


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cFormatStringPrecisionWithinBounds::cFormatStringPrecisionWithinBounds(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cFormatStringPrecisionWithinBounds::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);

	std::vector<llvm::StringRef> sinkTypes = {"strcpy", "strncpy", "sprintf", "snprintf"};

	std::string feature = "-1";


	if(bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass) {

		clang::CallExpr* call = llvm::dyn_cast<clang::CallExpr>(bof.GetSink());


		if (std::find(sinkTypes.begin(), sinkTypes.end(), call->getDirectCallee()->getName()) != sinkTypes.end())
		{

			llvm::outs() << call->getDirectCallee()->getName();

		}

	} else {

		feature = "-1";
	}


	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
