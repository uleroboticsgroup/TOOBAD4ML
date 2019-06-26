#include "IsCharacterCaseConversionSink.h"
#include "description/BufferOverflow.h"

using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cIsCharacterCaseConversionSink::cIsCharacterCaseConversionSink(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cIsCharacterCaseConversionSink::ExtractFeature(
		cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg,
				bof);

	std::vector<llvm::StringRef> sinkTypes = {"toupper", "tolower"};

	std::string feature = "-1";

	if(bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
		if(clang::BinaryOperator* binaryOperator = llvm::dyn_cast<clang::BinaryOperator>(bof.GetSink())) {
			if(binaryOperator->getRHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass) {
				if(clang::CallExpr* call = llvm::dyn_cast<clang::CallExpr>(binaryOperator->getRHS()->IgnoreCasts())){
					if (std::find(sinkTypes.begin(), sinkTypes.end(),
							call->getDirectCallee()->getName()) != sinkTypes.end()) {
						feature = "1";
					}
				}
			}
			else {
				feature = "0";
			}
		}
	}

	return decoratedFeature.append(feature).append(
			cDescriptorDecorator::FEATURE_SEPARATOR);
}
