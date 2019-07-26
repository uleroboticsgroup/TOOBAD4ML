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

	if (bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass && 
		bof.GetBuffer() != nullptr) {
		
		clang::BinaryOperator* sinkBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(bof.GetSink());

		// destinationSize -> calculate with refactored function.

		if (sinkBinaryOperator->getLHS()->getStmtClass() == clang::Stmt::StmtClass::ArraySubscriptExprClass) {
			clang::ArraySubscriptExpr* sinkArraySubscriptExpr =  llvm::dyn_cast_or_null<clang::ArraySubscriptExpr>(sinkBinaryOperator->getLHS());
		

			switch (sinkArraySubscriptExpr->getRHS()->getStmtClass()) {

				case clang::Stmt::StmtClass::IntegerLiteralClass: {
					indexArray = llvm::dyn_cast_or_null<clang::IntegerLiteral>(sinkArraySubscriptExpr->getRHS())->getValue().getLimitedValue();
				}

				break;

				// What else?
			}
			
			if(indexArray < destinationSize){
				feature = "1"; // good
			} else {
				feature = "0"; // bad
			}
		}
	}
	
	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
// Do we really need to check this? You break the string but you write in a valid place of memory.

//in case of char array is must check de last char is null term
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