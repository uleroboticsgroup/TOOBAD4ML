#include "description/SourceBufferAmbiguous.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
#include "ASTTraversal/FindVariableVisitor.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cSourceBufferAmbiguous::cSourceBufferAmbiguous(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cSourceBufferAmbiguous::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    std::string feature = "0";
    bool userWrite = false;
    bool normalWrite = false;

    cExprUtils* exprUtils = cExprUtils::GetInstance();
    SinkPathGraph spg = cpg.GetSPG(*(bof.GetSink()));
    clang::DeclRefExpr* srcBuffer = bof.GetBuffer(BufferType::SRC);

    std::map<std::string, int> sinkTypes = {
    { "strcpy", 0 }, { "strncpy", 0 },
    { "strcat", 0 }, { "strncat", 0 },
    { "memcpy",  0}, { "memmove", 0 },
    { "sprintf", 0 }, { "snprintf", 0 }
    };

    std::map<std::string, int> userSinkTypes = {
    { "gets", 0 }, { "fgets", 0 },
    { "scanf", 1 },{ "sscanf", 0 }
    };
    
    if(srcBuffer){
        // CODE FROM DESTINATION WRITES -> COULD BE REFACTORED
        for(clang::CFGStmt stmt: spg) {
            if (stmt.getStmt()->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
                clang::BinaryOperator* bop = const_cast<clang::BinaryOperator*>(llvm::dyn_cast<clang::BinaryOperator>(stmt.getStmt()));
                clang::Expr* leftPart = bop->getLHS()->IgnoreCasts()->IgnoreParens();
                if (leftPart->getStmtClass() == clang::Stmt::StmtClass::ArraySubscriptExprClass){
                    clang::Expr* current = llvm::dyn_cast<clang::ArraySubscriptExpr>(leftPart)->getLHS()->IgnoreCasts();
                    switch(current->getStmtClass()) {
                        case clang::Stmt::StmtClass::DeclRefExprClass: {
                            if(llvm::dyn_cast<clang::DeclRefExpr>(current)->getDecl() == srcBuffer->getDecl()){
                                normalWrite = true;
                            }
                        }
                        break;
                        case clang::Stmt::StmtClass::MemberExprClass: {
                            clang::Expr* innerMemberExpr = llvm::dyn_cast<clang::MemberExpr>(current)->getBase();

                            switch(innerMemberExpr->getStmtClass()) {
                                case clang::Stmt::StmtClass::DeclRefExprClass: {
                                    if(llvm::dyn_cast<clang::DeclRefExpr>(innerMemberExpr)->getDecl() == srcBuffer->getDecl()){
                                        normalWrite = true;
                                    }
                                }
                                break;
                                case clang::Stmt::StmtClass::ArraySubscriptExprClass: {
                                    clang::DeclRefExpr* innerArraySubExpr = llvm::dyn_cast_or_null<clang::DeclRefExpr>(llvm::dyn_cast<clang::ArraySubscriptExpr>(leftPart)->getLHS()->IgnoreCasts());
                                    if(innerArraySubExpr && innerArraySubExpr->getDecl() == srcBuffer->getDecl()){
                                        normalWrite = true;
                                    }
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
                else if (leftPart->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass) {
                    clang::Expr* expr = exprUtils->getBufferFromUnaryOperator(leftPart);
                    if(expr && llvm::dyn_cast<clang::DeclRefExpr>(expr)->getDecl() == srcBuffer->getDecl()) {
                        normalWrite = true;
                    }
                }
            }
            else if (stmt.getStmt()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass){
                clang::CallExpr* call = const_cast<clang::CallExpr*>(llvm::dyn_cast<clang::CallExpr>(stmt.getStmt()));
                
                // NON USER CALLS
                std::map<std::string, int>::iterator argPosition = sinkTypes.find(call->getDirectCallee()->getName());
                if(argPosition != sinkTypes.end()){
                    clang::Expr* arg = call->getArg(argPosition->second)->IgnoreCasts()->IgnoreParens();
                    if(arg->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass) {
                        arg = llvm::dyn_cast<clang::UnaryOperator>(arg)->getSubExpr();
                    }
                    
                    if(arg->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
                        if(llvm::dyn_cast<clang::DeclRefExpr>(arg)->getDecl() == srcBuffer->getDecl()){
                            normalWrite = true;
                        }
                    }
                }

                // USER CALLS
                argPosition = userSinkTypes.find(call->getDirectCallee()->getName());
                if(argPosition != userSinkTypes.end()){
                    clang::Expr* arg = call->getArg(argPosition->second)->IgnoreCasts()->IgnoreParens();
                    if(arg->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass) {
                        arg = llvm::dyn_cast<clang::UnaryOperator>(arg)->getSubExpr();
                    }
                    
                    if(arg->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass) {
                        if(llvm::dyn_cast<clang::DeclRefExpr>(arg)->getDecl() == srcBuffer->getDecl()){
                            userWrite = true;
                        }
                    }
                }
            }
        }
    }

    if (userWrite && normalWrite) {
        feature = "1";
    }
    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
