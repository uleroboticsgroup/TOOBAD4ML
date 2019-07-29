#include "description/BufferOverflow.h"
#include "StringCopyWithinBounds.h"

namespace TOOBAD4ML {

namespace description {


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cStringCopyWithinBounds::cStringCopyWithinBounds(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cStringCopyWithinBounds::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {
			
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);

	std::string feature = "-1";
	unsigned destination = 0;
	unsigned source = 0;

	std::vector<std::string> sinkTypes = {"strcpy"}; //sinks type 1

	if (bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass && 
		bof.GetBuffer(BufferType::DST) != nullptr) {
			
		clang::CallExpr* sinkCallExpr = llvm::dyn_cast<clang::CallExpr>(bof.GetSink());


		// TODO --- SAME PROBLEM :: get size of destination buffer
		if(auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(bof.GetBuffer(BufferType::DST)->getType().getTypePtr())) {
			destination = t->getSize().getLimitedValue();
		}


		if (sinkCallExpr->getDirectCallee()->getName() == "strcpy" && 
			sinkCallExpr->getNumArgs() == 2) {

			clang::Expr* argumentExpr = sinkCallExpr->getArg(1)->IgnoreCasts();

			switch (argumentExpr->getStmtClass()) {
				case clang::Stmt::StmtClass::StringLiteralClass: {
					clang::StringLiteral* argStrLiteral = llvm::dyn_cast<clang::StringLiteral>(argumentExpr);

					source = argStrLiteral->getLength();
					feature = ((source != 0 && source < destination) ? "1" : "0");
				}
				break;

				case clang::Stmt::StmtClass::DeclRefExprClass:
				break;

				default:
					feature = 2;
				break;
			}
		}
	}

	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}

}  /* namespace  description */

} /* namespace TOOBAD4ML */
