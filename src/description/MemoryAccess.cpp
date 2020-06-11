#include "description/MemoryAccess.h"
#include "description/BufferOverflow.h"
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cMemoryAccess::cMemoryAccess(IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};


// INHERITED METHODS
// ----------------------------------------------------------------------------

std::string cMemoryAccess::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
			cDescriptorDecorator::ExtractFeature(cpg, bof);

	std::string feature = "-1";
	
    std::map<std::string, std::string> writeTypes = {
        // String copy 
        { "strcpy", "1" }, { "strncpy", "1" },
        // String concatenation 
        { "strcat", "2" }, { "strncat", "2" },
        // Memory alteration
        { "memcpy", "3" }, { "memmove", "3" },
        // Formatted string output
        { "sprintf", "4" }, { "snprintf", "4" }
    }

    std::map<std::string, std::string> readTypes = {
        // Unformatted string input
        { "gets", "5" }, { "fgets", "5" },
        // Formatted string input
        { "scanf", "6" },{ "sscanf", "6" }
    };



	if (bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
        clang::BinaryOperator* bo = llvm::dyn_cast_or_null<clang::BinaryOperator>(bof.GetSink()->IgnoreCasts());

        if (bo->getLHS()->IgnoreCasts()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass)        
        feature = "2";


	}
    
    if (bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass){
		


		clang::CallExpr* sinkCallExpr = llvm::dyn_cast<clang::CallExpr>(bof.GetSink());

		std::map<std::string, std::string>::iterator sinkTypesIt = sinkTypes.find(sinkCallExpr->getDirectCallee()->getName());

		if(sinkTypesIt != sinkTypes.end()) {
			feature = sinkTypesIt->second;
		}

	}

	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
