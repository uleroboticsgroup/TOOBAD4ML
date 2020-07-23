#include "description/Declaration.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cDeclaration::cDeclaration(IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};


std::string cDeclaration::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
			cDescriptorDecorator::ExtractFeature(cpg, bof);

	std::string feature = "-1";

	cExprUtils* exprUtils = cExprUtils::GetInstance();
    SinkPathGraph spg = cpg.GetSPG(*(bof.GetSink()));
    clang::DeclRefExpr* dstBuffer = bof.GetBuffer(BufferType::DST);
    
	if(bof.GetBuffer(BufferType::DST)) {
		feature = "0";
		for(clang::CFGStmt stmt: spg) {
			if (stmt.getStmt()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
				clang::BinaryOperator* bop = const_cast<clang::BinaryOperator*>(llvm::dyn_cast<clang::BinaryOperator>(stmt.getStmt()));

				if (llvm::dyn_cast_or_null<clang::DeclRefExpr>(bop->getLHS()->IgnoreCasts()->IgnoreParens()) && llvm::dyn_cast_or_null<clang::DeclRefExpr>(bop->getLHS()->IgnoreCasts()->IgnoreParens())->getDecl() == bof.GetBuffer(BufferType::DST)->getDecl()) {

					if (bop->getRHS()->IgnoreCasts()->IgnoreParens()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass) {
						clang::CallExpr* call = llvm::dyn_cast_or_null<clang::CallExpr>(bop->getRHS()->IgnoreCasts()->IgnoreParens());

						if(call->getDirectCallee()->getNameAsString() == "malloc") {
							clang::Expr* sizeExpr = call->getArg(0)->IgnoreCasts()->IgnoreParens();

							// Just the variable
							if(llvm::dyn_cast_or_null<clang::DeclRefExpr>(sizeExpr) && llvm::dyn_cast<clang::DeclRefExpr>(sizeExpr)->getDecl() == bof.GetBuffer(BufferType::SRC)->getDecl()) {
								feature = "1";
							}
							// Item of the buffer
							else if(llvm::dyn_cast_or_null<clang::ArraySubscriptExpr>(sizeExpr)){

								if(llvm::dyn_cast_or_null<clang::DeclRefExpr>(llvm::dyn_cast<clang::ArraySubscriptExpr>(sizeExpr)->getLHS()->IgnoreCasts()->IgnoreParens()) &&
								   llvm::dyn_cast_or_null<clang::DeclRefExpr>(llvm::dyn_cast<clang::ArraySubscriptExpr>(sizeExpr)->getLHS()->IgnoreCasts()->IgnoreParens())->getDecl()== bof.GetBuffer(BufferType::SRC)->getDecl()) {
								
									feature = "1";
								}
								else if(exprUtils->isExprInsideExpr(sizeExpr, bof.GetBuffer(BufferType::SRC))) {
									feature = "4";
								}
								else {
									feature = "2";
								}
							}
							// BOP
							else if(llvm::dyn_cast_or_null<clang::BinaryOperator>(sizeExpr)){
								clang::BinaryOperator* bop2 = llvm::dyn_cast<clang::BinaryOperator>(sizeExpr);

								if(exprUtils->isExprInsideExpr(bop2, bof.GetBuffer(BufferType::SRC))) {
									feature = "4";
								}
								else {
									feature = "2";
								}

							}
							else if(llvm::dyn_cast_or_null<clang::UnaryOperator>(sizeExpr)){
									
								if( llvm::dyn_cast_or_null<clang::DeclRefExpr>(llvm::dyn_cast<clang::UnaryOperator>(sizeExpr)->getSubExpr()->IgnoreCasts()->IgnoreParens()) &&
									llvm::dyn_cast_or_null<clang::DeclRefExpr>(llvm::dyn_cast<clang::UnaryOperator>(sizeExpr)->getSubExpr()->IgnoreCasts()->IgnoreParens())->getDecl()== bof.GetBuffer(BufferType::SRC)->getDecl()) {
									feature = "1";
								}
								else if(exprUtils->isExprInsideExpr(sizeExpr, bof.GetBuffer(BufferType::SRC))) {
									feature = "4";
								}
								else {
									feature = "2";
								}
								
							}
							else if(llvm::dyn_cast_or_null<clang::IntegerLiteral>(sizeExpr)){
								feature = "3";
							}

						}
					}
				}
			}
		}
	}

	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}