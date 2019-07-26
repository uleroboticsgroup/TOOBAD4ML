#include "IsCharacterCaseConversionSink.h"
#include "description/BufferOverflow.h"
#include "iostream"
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

	std::string feature = "-1";
	std::vector<std::string> sinkTypes = {"toupper", "tolower"};

	if(bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
		clang::BinaryOperator* sinkBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(bof.GetSink());
			if(sinkBinaryOperator->getRHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass) {

				clang::CallExpr* rightCallExpr = llvm::dyn_cast<clang::CallExpr>(sinkBinaryOperator->getRHS()->IgnoreCasts());

				if (std::find(sinkTypes.begin(), sinkTypes.end(),
						rightCallExpr->getDirectCallee()->getName()) != sinkTypes.end()) {
					feature = "1";
				}
				
			}
			else {
				// ?????????? why 0 here
				feature = "0";
			}
		
	}

	return decoratedFeature.append(feature).append(
			cDescriptorDecorator::FEATURE_SEPARATOR);
}
