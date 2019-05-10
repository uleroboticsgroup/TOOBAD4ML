#include "description/NumberOfElementsCopiedWithinBounds.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
// ----------------------------------------------------------------------------

using namespace TOOBAD4ML;
using namespace description;


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cNumberOfElementsCopiedWithinBounds::cNumberOfElementsCopiedWithinBounds(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cNumberOfElementsCopiedWithinBounds::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);

	std::vector<llvm::StringRef> sinkTypes = {"strncpy"};

	std::string feature = "-1";
	unsigned limit = 0;
	unsigned destination = 0;

	if (bof.GetSink()->getStmtClass()
			== clang::Stmt::StmtClass::CallExprClass) {

		if(clang::CallExpr* call = llvm::dyn_cast<clang::CallExpr>(bof.GetSink())){

			if (std::find(sinkTypes.begin(), sinkTypes.end(),
					call->getDirectCallee()->getName()) != sinkTypes.end()) {

				// get size of destination buffer
				if(auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(bof.GetBuffer()->getType().getTypePtr())) {
					destination = t->getSize().getLimitedValue();
				}

				if(call->getDirectCallee()->getName() == "strncpy") {

					// strncpy(destination, source, limit)
					if(call->getNumArgs() == 3){

						// get limit to be copied
						if(clang::Expr* s = call->getArg(2)->IgnoreCasts()) {

							std::string name = s->getStmtClassName();

							if(name.compare("IntegerLiteral") == 0) {

								clang::IntegerLiteral* intLiteral = llvm::dyn_cast<clang::IntegerLiteral>(s);

								limit = intLiteral->getValue().getLimitedValue();

								feature = ((limit != 0 && limit < destination) ? "1" : "0");

							} else if(name.compare("UnaryExprOrTypeTraitExpr") == 0) { // strncpy(str4, str3, sizeof(str4))

								clang::UnaryExprOrTypeTraitExpr* u = llvm::dyn_cast<clang::UnaryExprOrTypeTraitExpr>(s);

								if(clang::DeclRefExpr* declExpr = llvm::dyn_cast<clang::DeclRefExpr>(u->getArgumentExpr()->IgnoreParenCasts())) {

									if (auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(declExpr->getType().getTypePtr())) {

											limit = t->getSize().getLimitedValue();

											feature = ((limit != 0 && limit < destination) ? "1" : "0");
									}

								}


							} else { // when cannot be evaluated
								feature = "2";
							}

						}
					}

				}

			}
		}

	} else { // if sink is not type of sinkTypes
		feature = "-1";
	}

	return decoratedFeature.append(feature.append(cDescriptorDecorator::FEATURE_SEPARATOR));


}


//	   clang::FunctionDecl* funcDecl = fun.getFunctionDecl();
//
//	   if(funcDecl->getNumParams() == 3) { // strncpy
//
//		   llvm::outs() << clang::QualType::getAsString(funcDecl->getParamDecl(1)->getType().split()) << "\n";
//
//		  clang::Decl *d =  bof.GetBuffer()->getReferencedDeclOfCallee();
//
//		  if(clang::VarDecl *var = llvm::dyn_cast<clang::VarDecl>(d)) {
//
//			   if(auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(var->getType().getTypePtr())) {
//
//				   llvm::outs() << "BINGOOOOOOOOO\n";
//				    t->getSize().dump();
//				   llvm::outs() << t->getSize().getLimitedValue() << "\n";
//
//			   }
//		  }
	  // }

//		   if(auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(var->getType().getTypePtr())) {
//
//			   llvm::outs() << "BINGOOOOOOOOO\n";
//		   }

//	clang::FunctionDecl* funcDecl = fun.getFunctionDecl();
//
//	if(funcDecl->getNumParams() == 3)
//
//		   funcDecl->getParamDecl(2)->dumpColor();
//
//		   clang::ParmVarDecl* parm = funcDecl->getParamDecl(2);
//
//		   clang::VarDecl* var = parm->getActingDefinition();
//		   clang::TypeInfo info =  var->getASTContext().getTypeInfo(var->getType());
//		   llvm::outs() << var->getNameAsString() << "SIZE--" << info.Width << info.Align << "\n";
//	  }

	//}

