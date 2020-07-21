#include "description/InputCount.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cInputCount::cInputCount(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cInputCount::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    int feature = 0;
    
    std::map<std::string, int> sinkTypes = {
    { "strcpy", 0 }, { "strncpy", 0 },
    { "strcat", 0 }, { "strncat", 0 },
    { "memcpy",  0}, { "memmove", 0 },
    { "sprintf", 0 }, { "snprintf", 0 },
    { "gets", 0 }, { "fgets", 0 },
    { "scanf", 1 },{ "sscanf", 0 }};

    cExprUtils* exprUtils = cExprUtils::GetInstance();
    SinkPathGraph spg = cpg.GetSPG(*(bof.GetSink()));

    for(clang::CFGStmt stmt: spg) {
        if (stmt.getStmt()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
            clang::BinaryOperator* bop = const_cast<clang::BinaryOperator*>(llvm::dyn_cast<clang::BinaryOperator>(stmt.getStmt()));
            clang::Expr* leftPart = bop->getLHS()->IgnoreCasts()->IgnoreParens();
            if (leftPart->getStmtClass() == clang::Stmt::StmtClass::ArraySubscriptExprClass){
                if(llvm::dyn_cast<clang::DeclRefExpr>(llvm::dyn_cast<clang::ArraySubscriptExpr>(leftPart)->getLHS()->IgnoreCasts())->getDecl() == bof.GetBuffer(BufferType::SRC)->getDecl()){
                    feature += 1;
                }
            }
            else if (leftPart->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass) {
                clang::Expr* expr = exprUtils->getBufferFromUnaryOperator(leftPart);

                if(expr && llvm::dyn_cast<clang::DeclRefExpr>(expr)->getDecl() == bof.GetBuffer(BufferType::SRC)->getDecl()) {
                    feature += 1;
                }
            }
        }
        else if (stmt.getStmt()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass){
            clang::CallExpr* call = const_cast<clang::CallExpr*>(llvm::dyn_cast<clang::CallExpr>(stmt.getStmt()));
            std::map<std::string, int>::iterator argPosition = sinkTypes.find(call->getDirectCallee()->getName());
            if(argPosition != sinkTypes.end()){
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
    return decoratedFeature.append(std::to_string(feature)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
