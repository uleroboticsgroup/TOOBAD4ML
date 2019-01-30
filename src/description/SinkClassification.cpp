#include "description/SinkClassification.h"

using namespace TOOBAD4ML;
using namespace description;

cSinkClassification::cSinkClassification(IFeatureExtractor *decoratedComponent) :
		cFeatureExtractorDecorator(decoratedComponent) {
};

llvm::StringRef cSinkClassification::ExtractFeature(
		cCodePseudoPropertyGraph &cppg,
		cBufferOverflow &bufferOverflow) {

	std::string decoratedFeature =
			cFeatureExtractorDecorator::ExtractFeature(cppg, bufferOverflow);

	std::map<llvm::StringRef, llvm::StringRef> sinkTypes = {
			{ "strcpy", "1" }, { "strncpy", "1" },
			{ "strcat", "2" }, { "strncat", "2" },
			{ "memcpy", "3" }, { "memmove", "3" },
			{ "sprintf", "4" }, { "snprintf", "4" },
			{ "gets", "5" }, { "fgets", "5" },
			{ "scanf", "6" },{ "sscanf", "6" }, };

	std::string feature;

	//TODO Get rid of magic literals string to actual constants
	if (bufferOverflow.GetSinkType() == clang::Stmt::StmtClass::BinaryOperatorClass) {
		feature = "7";
	} else {
		// CallExpr
		for(clang::Stmt::child_iterator it = bufferOverflow.GetSink()->child_begin(); it != bufferOverflow.GetSink()->child_end(); it++) {
			// ImplicitCastExpr
			for(clang::Stmt::child_iterator it2 = it->child_begin(); it2 != it->child_end(); it2++) {
				//DeclRefExpr
				if(clang::DeclRefExpr* declRef =  llvm::dyn_cast<clang::DeclRefExpr>(*it2)){
					// Function or Var
					if(clang::ValueDecl* var = declRef->getDecl()) { // -> Function or Var
						// Function
						if(var->getKind() == clang::Decl::Function) { // -> Function
							feature = sinkTypes.find(var->getName())->second;
							break;
						}
					}
				}
			}
		}
	}

	llvm::outs() << "SinkClassification: " <<  feature << "\n";
	return decoratedFeature + feature.append(";");
}

