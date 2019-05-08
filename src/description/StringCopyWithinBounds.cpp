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

	std::vector<llvm::StringRef> sinkTypes = {"strcpy"}; //sinks type 1

	if (bof.GetSink()->getStmtClass()
				== clang::Stmt::StmtClass::CallExprClass) {

			if(clang::CallExpr* call = llvm::dyn_cast<clang::CallExpr>(bof.GetSink())) {


				// get size of destination buffer
				if(auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(bof.GetBuffer()->getType().getTypePtr())) {
					destination = t->getSize().getLimitedValue();
				}


				if (std::find(sinkTypes.begin(), sinkTypes.end(),
						call->getDirectCallee()->getName()) != sinkTypes.end()) {


					if(call->getDirectCallee()->getName() == "strcpy") {

						if(call->getNumArgs() == 2) {

							if(clang::Expr* s = call->getArg(1)->IgnoreCasts()) {

								std::string name = s->getStmtClassName();

								//TODO when the source is -DeclRefExpr
								if(name.compare("StringLiteral") == 0) {

									clang::StringLiteral* strLiteral = llvm::dyn_cast<clang::StringLiteral>(s);

									source = strLiteral->getLength();

									llvm::outs() <<  source << "\n";

									feature = (source < destination ? "1" : "0");


								} else { // when cannot be evaluated
									feature = "2";
								}
							}

						}


					}

				}


			}
	} else {
		feature = "-1";
	}



	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);

}





}  /* namespace  description */

} /* namespace TOOBAD4ML */
