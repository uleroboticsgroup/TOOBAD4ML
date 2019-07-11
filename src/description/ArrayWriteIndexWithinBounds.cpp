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
	unsigned destinationSize = 0;
	unsigned indexArray = 0;

	if(bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass && bof.GetBuffer() != nullptr) {

		if(clang::BinaryOperator* binaryOperator = llvm::dyn_cast<clang::BinaryOperator>(bof.GetSink())) {

			switch (binaryOperator->getLHS()->getStmtClass()) {

				case clang::Stmt::StmtClass::ArraySubscriptExprClass: {

					if(clang::ArraySubscriptExpr* arrayExpr =  llvm::dyn_cast_or_null<clang::ArraySubscriptExpr>(binaryOperator->getLHS())) {

						clang::IntegerLiteral* intLiteral  = llvm::dyn_cast_or_null<clang::IntegerLiteral>(arrayExpr->getRHS());

						if(intLiteral!=nullptr) {

							if(auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(bof.GetBuffer()->getType().getTypePtr())) {
								destinationSize = t->getSize().getLimitedValue();
							}

							indexArray = intLiteral->getValue().getLimitedValue();

//							//in case of char array is must check de last char is null term
//							if(clang::DeclRefExpr* Ref = llvm::dyn_cast_or_null<clang::DeclRefExpr>(bof.GetBuffer()) ) {
//								if(clang::VarDecl* VD = llvm::dyn_cast_or_null<clang::VarDecl>(Ref->getDecl())) {
//
//									if(const clang::InitListExpr* list =  llvm::dyn_cast_or_null<clang::InitListExpr>(VD->getAnyInitializer())) {
//										// last char \0
//										if(const clang::CharacterLiteral* nullTerminator = llvm::dyn_cast_or_null<clang::CharacterLiteral>(list->getInit(list->getNumInits()-1)->IgnoreCasts())) {
//
//											if(nullTerminator->getValue() == 0) {
//
//												unsigned indexTerminator = list->getNumInits() -1;
//
//												llvm::outs() << "aray" << indexArray << "termi" << indexTerminator << destinationSize << "destinationSize\n";
//
//												if((indexArray < destinationSize) && (indexArray != indexTerminator)){
//													feature = "1";// good
//												} else {
//													feature = "0"; // bad
//												}
//
//											} else {
//												llvm::outs() << "No hay null terminator\n";
//											}
//
//										}
//									}
//								}
//							}

//							// in anther case
//							else {

								if(indexArray < destinationSize){
									feature = "1"; // good
								} else {
									feature = "0"; // bad
								}


	//						}
						}
					}

				} break;

				default: feature = "-1";
			}

		} else {
			 feature = "-1";
		}
	} else {
		 feature = "-1";
	}

	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
