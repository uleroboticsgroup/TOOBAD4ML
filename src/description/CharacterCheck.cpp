#include "description/CharacterCheck.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
#include "iostream"

using namespace TOOBAD4ML;
using namespace description;

cCharacterCheck::cCharacterCheck(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

std::string cCharacterCheck::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    unsigned counter = 0;
    clang::DeclRefExpr* srcBuffer = bof.GetBuffer(BufferType::SRC);

    if (srcBuffer) {
        for (clang::Expr* sanitizationExpr: bof.GetSinkSanitizations()) {
            std::vector<clang::ValueDecl*> bufferValueDecls;

            if (sanitizationExpr->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sanitizationExpr);
                
                if(!clang::BinaryOperator::isAssignmentOp(condBinaryOperator->getOpcode())) {
                    if (condBinaryOperator->getLHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
                        bufferValueDecls.push_back(llvm::dyn_cast<clang::DeclRefExpr>(condBinaryOperator->getLHS()->IgnoreCasts())->getDecl());
                    }
                    else if (condBinaryOperator->getRHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
                        bufferValueDecls.push_back(llvm::dyn_cast<clang::DeclRefExpr>(condBinaryOperator->getRHS()->IgnoreCasts())->getDecl());
                    }

                    for(clang::ValueDecl* potentialBufferValueDecl: bufferValueDecls) {
                        if(potentialBufferValueDecl == srcBuffer->getDecl() && 
                           (potentialBufferValueDecl->getType().getTypePtr()->isSpecificBuiltinType(clang::BuiltinType::Char_S) ||
                            potentialBufferValueDecl->getType().getTypePtr()->isSpecificBuiltinType(clang::BuiltinType::Int))) {
                            
                            counter++;
                        }
                    }
                }
        
            }
        }
    }
    
    //

    return decoratedFeature.append(std::to_string(counter)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
