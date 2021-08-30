#include "description/SourceDependentLoopTermination.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
#include "ASTTraversal/FindVariableVisitor.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cSourceDependentLoopTermination::cSourceDependentLoopTermination(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cSourceDependentLoopTermination::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    std::string feature = "-1";
    int found = 0;

    clang::Expr* expr = bof.GetSink();
    clang::DeclRefExpr* source = bof.GetBuffer(BufferType::SRC);
    const clang::Stmt* stmt = const_cast<clang::Stmt*>(llvm::dyn_cast<clang::Stmt>(expr));
    const clang::Stmt* parent;

    while(stmt && !found) {
        const auto& parents = cpg.GetAST().getASTContext().getParents(*stmt);
        if (!parents.empty()) {
            parent = parents[0].get<clang::Stmt>();
        }

        if (parent && parent->getStmtClass() == clang::Stmt::StmtClass::WhileStmtClass) {
            found = 1;
        }
        else if (parent && parent->getStmtClass() == clang::Stmt::StmtClass::ForStmtClass) {
            found = 2;
        }

        stmt = parent;
    }

    if (found) {
        clang::Stmt* target;

        switch (found) {
            case 1: { // WHILE 
                clang::WhileStmt* whileStmt = llvm::dyn_cast<clang::WhileStmt>(const_cast<clang::Stmt*>(parent));
                target = whileStmt->getCond();
            }
            break;
            case 2: {
                clang::ForStmt* forStmt = llvm::dyn_cast<clang::ForStmt>(const_cast<clang::Stmt*>(parent));
                target = forStmt->getCond();
            }
            break;
        }
        ASTTraversal::cFindVariableVisitor visitor(source);
        visitor.TraverseStmt(target);
        if (visitor.IsFound()) {
            feature = "1";
        }
        else {
            feature = "0";
        }
    }

    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
