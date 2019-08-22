#include "description/CharacterOccurrenceStringCheck.h"
#include "description/BufferOverflow.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// NON CLASS METHODS
// ------------------------------------------------------------------------
bool isTargetFunction(clang::CallExpr* functionCallExpr, clang::ValueDecl* srcBuffer) {
    std::map<std::string, int> targetFunctions = {{"strchr", 0}, {"strpbrk", 0}, {"memchar", 0}};
    std::string functionName = functionCallExpr->getDirectCallee()->getNameAsString();

    if (targetFunctions.count(functionName)){
        clang::DeclRefExpr* argDeclRefExpr = llvm::dyn_cast<clang::DeclRefExpr>(functionCallExpr->getArg(targetFunctions[functionName])->IgnoreCasts());

        if (argDeclRefExpr->getDecl() == srcBuffer) {
            return true;
        }
    }  
    
    return false;
}

// CONSTRUCTORS & DESTRUCTORS
// ------------------------------------------------------------------------
cCharacterOccurrenceStringCheck::cCharacterOccurrenceStringCheck(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cCharacterOccurrenceStringCheck::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    cExprUtils* exprUtils = cExprUtils::GetInstance();

    unsigned counter = 0;
    clang::ValueDecl* bufferValueDecl = nullptr;
    clang::CallExpr* callExpr = nullptr;
    clang::DeclRefExpr* srcBuffer = bof.GetBuffer(BufferType::SRC);

    if (srcBuffer) {    
        for (clang::Expr* sanitizationExpr: bof.GetSinkSanitizations()) {

            if (sanitizationExpr->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* condBinaryOperator = llvm::dyn_cast<clang::BinaryOperator>(sanitizationExpr);
                std::vector<clang::Expr*> functionCallExprs = exprUtils->getFromComparisonBinaryOperator(condBinaryOperator, clang::Stmt::StmtClass::CallExprClass);

                for(clang::Expr* functionCallExpr: functionCallExprs) {
                    if (isTargetFunction(llvm::dyn_cast<clang::CallExpr>(functionCallExpr), srcBuffer->getDecl())) {
                        counter++;
                    }
                }        
            }

            else if (sanitizationExpr->getStmtClass() == clang::Stmt::StmtClass::CallExprClass) {
                clang::CallExpr* functionCallExpr = llvm::dyn_cast<clang::CallExpr>(sanitizationExpr);

                if (isTargetFunction(functionCallExpr, srcBuffer->getDecl())) {
                    counter++;
                }
            }
        }
    }

    return decoratedFeature.append(std::to_string(counter)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
