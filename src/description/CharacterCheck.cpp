#include "description/CharacterCheck.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;
// ------------------------------------------------------------------------

// CONSTRUCTORS & DESTRUCTORS
// ------------------------------------------------------------------------
cCharacterCheck::cCharacterCheck(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cCharacterCheck::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    unsigned counter = 0;
    clang::DeclRefExpr* srcBuffer = bof.GetBuffer(BufferType::SRC);

    if (srcBuffer) {
        for (clang::Expr* sanitizationExpr: bof.GetSinkSanitizations()) {

            if (sanitizationExpr->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sanitizationExpr);
                
                std::vector<clang::Expr*> bufferDeclRefExprs = exprUtils->getFromComparisonBinaryOperator(condBinaryOperator, clang::Stmt::StmtClass::DeclRefExprClass);

                for (clang::Expr* bufferDeclRefExpr: bufferDeclRefExprs) {
                    clang::ValueDecl* potentialBufferValueDecl = exprUtils->getValueFromDeclRefExpr(llvm::dyn_cast<clang::DeclRefExpr>(bufferDeclRefExpr));

                    if(potentialBufferValueDecl == srcBuffer->getDecl() && 
                        (potentialBufferValueDecl->getType().getTypePtr()->isSpecificBuiltinType(clang::BuiltinType::Char_S) ||
                        potentialBufferValueDecl->getType().getTypePtr()->isSpecificBuiltinType(clang::BuiltinType::Int))) {
                        
                        counter++;
                        break;
                    }   
                }
            }
        }
    }
    
    //

    return decoratedFeature.append(std::to_string(counter)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
