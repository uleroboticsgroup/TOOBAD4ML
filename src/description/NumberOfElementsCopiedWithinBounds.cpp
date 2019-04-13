#include "description/NumberOfElementsCopiedWithinBounds.h"
#include "description/BufferOverflow.h"
#include "ASTTraversal/FindFunctionVisitor.h"
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

	std::vector<llvm::StringRef> sinkTypes = {"strcpy", "strncpy"};

	ASTTraversal::cFindFunctionVisitor fun(bof.GetSink());
			fun.TraverseStmt(bof.GetSink());

	std::string feature = "";
	unsigned source = 0;
	unsigned destination = 0;
	unsigned limit = 0;

	if (std::find(sinkTypes.begin(), sinkTypes.end(), fun.getFunctionName()) != sinkTypes.end())
	{
		clang::CallExpr* call = llvm::dyn_cast<clang::CallExpr>(bof.GetSink());

		// get size of destination buffer
		if(auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(bof.GetBuffer()->getType().getTypePtr())) {
			destination = t->getSize().getLimitedValue();
		}

		if(fun.getFunctionName() == "strcpy") {

			// get size of source
			if(clang::Expr* s = call->getArg(1)->IgnoreCasts()) {
				//uint64_t size;
				//s->tryEvaluateObjectSize(size, cpg.GetAST().getASTContext(), clang::Type::VariableArray);

				std::string name = s->getStmtClassName();

				//TODO when the source is -DeclRefExpr array
				if(name.compare("StringLiteral") == 0) {

					llvm::outs() << "StringLiteralStringLiteralStringLiteralStringLiteral" << "\n";

					clang::StringLiteral* strLiteral = llvm::dyn_cast<clang::StringLiteral>(s);

					source = strLiteral->getLength() + 1;

					llvm::outs() <<  source << "\n";

				} else { // when cannot be evaluated
					feature = "2";
				}
			}

		} else if(fun.getFunctionName() == "strncpy") {

			// strncpy(destination, source, limit)

			// get size of source buffer
			if(auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(call->getArg(1)->IgnoreCasts()->getType().getTypePtr())) {
				source = t->getSize().getLimitedValue();
			}

			// get limit to be copied
			if(clang::Expr* s = call->getArg(2)->IgnoreCasts()) {
				//uint64_t size;
				//s->tryEvaluateObjectSize(size, cpg.GetAST().getASTContext(), clang::Type::VariableArray);

				std::string name = s->getStmtClassName();

				//TODO when the source is -DeclRefExpr array
				if(name.compare("IntegerLiteral") == 0) {

					llvm::outs() << "INTEGER LITERAL" << "\n";

					clang::IntegerLiteral* intLiteral = llvm::dyn_cast<clang::IntegerLiteral>(s);

					// if source is greater limit adding '\0'
					if(source > limit){
						limit = intLiteral->getValue().getLimitedValue() + 1;
					}
					else { // need add '\0' manually
						limit = intLiteral->getValue().getLimitedValue() + 1;
					}

					llvm::outs() <<  limit << "\n";

				} else { // when cannot be evaluated
					feature = "2";
				}
			}
		}

		if(feature.empty()){
			// if the number of elements to be copied is no greater than destination
			if(source<=destination) {
				feature = "1";
			} else if(source>destination) {
				feature = "0";
			}
		}

	} else { // if sink is not type of sinkTypes
		feature = "-1";
	}

	llvm::outs() << "FEATURE NUMBER OF ELEMENT COPIED" << feature << "\n";

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

