#include "description/ArrayWriteIndexWithinBounds.h"
#include "description/BufferOverflow.h"


// ----------------------------------------------------------------------------

using namespace TOOBAD4ML;
using namespace description;


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cArrayWriteIndexWithinBounds::cArrayWriteIndexWithinBounds(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cArrayWriteIndexWithinBounds::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);

	std::string feature = "-1";

	if(bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {

		if(clang::BinaryOperator* binaryOperator = llvm::dyn_cast<clang::BinaryOperator>(bof.GetSink())) {

			switch (binaryOperator->getLHS()->getStmtClass()) {

				case clang::Stmt::StmtClass::ArraySubscriptExprClass: {

					if(clang::ArraySubscriptExpr* arrayExpr =  llvm::dyn_cast_or_null<clang::ArraySubscriptExpr>(binaryOperator->getLHS())) {

						clang::IntegerLiteral* indexArray =  llvm::dyn_cast_or_null<clang::IntegerLiteral>(arrayExpr->getRHS());

						if(indexArray!=nullptr && bof.GetBuffer() != nullptr) {
							feature = "1";
						} else {
							feature = "0";
						}
					}

				} break;
			}

		} else {
			 feature = "-1";
		}
	}

	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
