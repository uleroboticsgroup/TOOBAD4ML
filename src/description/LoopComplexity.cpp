#include "description/LoopComplexity.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cLoopComplexity::cLoopComplexity(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cLoopComplexity::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    std::string feature = "-1";
    bool applicable = false;

    clang::Expr* expr = bof.GetSink();
    const clang::Stmt* stmt = const_cast<clang::Stmt*>(llvm::dyn_cast<clang::Stmt>(expr));
    const clang::Stmt* parent;

    while(stmt) {
        const auto& parents = cpg.GetAST().getASTContext().getParents(*stmt);
        if (!parents.empty()) {
            parent = parents[0].get<clang::Stmt>();
        }

        if (parent && parent->getStmtClass() == clang::Stmt::StmtClass::WhileStmtClass) {
            break;
        }
        else if (parent && parent->getStmtClass() == clang::Stmt::StmtClass::ForStmtClass) {
            applicable = true;
            break;
        }

        stmt = parent;
    }

    if (applicable) {
        clang::ForStmt* forStmt = llvm::dyn_cast<clang::ForStmt>(const_cast<clang::Stmt*>(parent));
        clang::Stmt* init = forStmt->getInit(); 
        clang::Expr* cond = llvm::dyn_cast<clang::Expr>(forStmt->getCond()); 
        clang::Expr* increment = llvm::dyn_cast<clang::Expr>(forStmt->getInc());
    
        int counter = 0;
        if (init && init->getStmtClass() == clang::Stmt::StmtClass::DeclStmtClass){
            clang::DeclStmt* declStmt = llvm::dyn_cast<clang::DeclStmt>(init);
            clang::Decl* variableDecl = declStmt->getSingleDecl();

            if (llvm::dyn_cast<clang::VarDecl>(variableDecl)) {
                clang::VarDecl* var = llvm::dyn_cast<clang::VarDecl>(variableDecl);
                if (!var->getType().getTypePtr()->isIntegerType()) {
                    counter += 1;
                }
            }
        } else {
            counter += 1;
        } 

        if (cond && cond->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass){
            clang::BinaryOperator* condBOP = llvm::dyn_cast<clang::BinaryOperator>(cond);

            if (!condBOP->getLHS()->IgnoreCasts()->IgnoreParens()->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass ||
                !condBOP->getLHS()->IgnoreCasts()->IgnoreParens()->getStmtClass() == clang::Stmt::StmtClass::IntegerLiteralClass) {
                    counter += 1;
                    condBOP->dumpColor();
                }
        } else {
            counter += 1;
        } 

        if (increment && increment->getStmtClass() == clang::Stmt::StmtClass::UnaryOperatorClass){
            clang::UnaryOperator* incrementUOP = llvm::dyn_cast<clang::UnaryOperator>(increment);
            if(!incrementUOP->isIncrementOp()) {
                counter += 1;
                incrementUOP->dumpColor();
            }

        } else {
            counter += 1;
        }  

        feature = std::to_string(counter);
    }


    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
