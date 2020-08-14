#include "description/InputsWithLimiting.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
#include "iostream"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cInputsWithLimiting::cInputsWithLimiting(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cInputsWithLimiting::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    int feature = 0;
    
    std::map<std::string, int> secureSinkInputCalls = {
    { "strncpy", 0 }, { "strncat", 0 },
    { "memcpy",  0}, { "memmove", 0 },
    { "snprintf", 0 }, { "fgets", 0 }};

    cExprUtils* exprUtils = cExprUtils::GetInstance();
    SinkPathGraph spg = cpg.GetSPG(*(bof.GetSink()));

    if (bof.GetBuffer(BufferType::SRC)) {
        for(clang::CFGStmt stmt: spg) {
            if (stmt.getStmt()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass){
                clang::CallExpr* call = const_cast<clang::CallExpr*>(llvm::dyn_cast<clang::CallExpr>(stmt.getStmt()));
                std::map<std::string, int>::iterator argPosition = secureSinkInputCalls.find(call->getDirectCallee()->getName());
                if(argPosition != secureSinkInputCalls.end()){
                    clang::Expr* arg = call->getArg(argPosition->second)->IgnoreCasts()->IgnoreParens();
                    if(arg->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass) {
                        arg = llvm::dyn_cast<clang::UnaryOperator>(arg)->getSubExpr();
                    }
                    
                    if(arg->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
                        if(llvm::dyn_cast<clang::DeclRefExpr>(arg)->getDecl() == bof.GetBuffer(BufferType::SRC)->getDecl()){
                            feature += 1;
                        }
                    }
                }

            }
        }
    }

    return decoratedFeature.append(std::to_string(feature)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
