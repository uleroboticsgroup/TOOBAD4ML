#include "description/MemoryAccess.h"
#include "description/BufferOverflow.h"
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cMemoryAccess::cMemoryAccess(IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};


int checkCallType(clang::CallExpr* callExpr, int counter) {
    std::map<std::string, std::string> writeTypes = {
        // String copy 
        { "strcpy", "1" }, { "strncpy", "1" },
        // String concatenation 
        { "strcat", "2" }, { "strncat", "2" },
        // Memory alteration
        { "memcpy", "3" }, { "memmove", "3" },
        // Formatted string output
        { "sprintf", "4" }, { "snprintf", "4" },
        // Unformatted string input
        { "gets", "5" }, { "fgets", "5" },
        // Formatted string input
        { "scanf", "6" },{ "sscanf", "6" }
    };

    std::map<std::string, std::string>::iterator writeTypesIt = writeTypes.find(callExpr->getDirectCallee()->getName());
    if(writeTypesIt != writeTypes.end()) {
        counter = 2;
    }

    return counter;
}

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cMemoryAccess::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
			cDescriptorDecorator::ExtractFeature(cpg, bof);

	std::string feature = "-1";
	int counter = 0;

	if (bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
        clang::BinaryOperator* bo = llvm::dyn_cast_or_null<clang::BinaryOperator>(bof.GetSink()->IgnoreCasts());

        // Right side of assignment
        if (bo->getRHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass) {
    		clang::CallExpr* sinkRHSCallExpr = llvm::dyn_cast<clang::CallExpr>(bo->getRHS()->IgnoreCasts());
            counter = checkCallType(sinkRHSCallExpr, counter);
        }
        else if (bo->getRHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::ArraySubscriptExprClass) {
            if (counter != 1){
                counter += 1;
            }
        }
        else if (bo->getRHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass) {
            std::string operation = clang::UnaryOperator::getOpcodeStr(llvm::dyn_cast_or_null<clang::UnaryOperator>(bo->getRHS()->IgnoreCasts())->getOpcode()).str();

            if (operation == "*") {
                if (counter != 1){
                    counter += 1;
                }            
            }
        }


        // Left side of assignment
        if (bo->getLHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::ArraySubscriptExprClass) {
            if (counter != 1){
                counter += 1;
            }
        }
        else if (bo->getLHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass) {
            std::string operation = clang::UnaryOperator::getOpcodeStr(llvm::dyn_cast_or_null<clang::UnaryOperator>(bo->getLHS()->IgnoreCasts())->getOpcode()).str();

            if (operation == "*") {
                if (counter != 1){
                    counter += 1;
                }            
            }
        }
	}
    // If its just a call
    else if (bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass){
		clang::CallExpr* sinkCallExpr = llvm::dyn_cast<clang::CallExpr>(bof.GetSink());
        counter = checkCallType(sinkCallExpr, counter);
	}

	return decoratedFeature.append(std::to_string(counter)).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
