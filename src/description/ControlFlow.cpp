#include "description/ControlFlow.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
#include "ASTTraversal/FindVariableVisitor.h"
#include "iostream"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cControlFlow::cControlFlow(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cControlFlow::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    std::string feature = "0";

    cExprUtils* exprUtils = cExprUtils::GetInstance();
    SinkPathGraph spg = cpg.GetSPG(*(bof.GetSink()));

    clang::Expr* expr = bof.GetSink();
    const clang::Stmt* stmt = const_cast<clang::Stmt*>(llvm::dyn_cast<clang::Stmt>(expr));
    const clang::Stmt* parent;

    while(feature == "0" && stmt) {
        const auto& parents = cpg.GetAST().getASTContext().getParents(*stmt);
        if (!parents.empty()) {
            parent = parents[0].get<clang::Stmt>();
        }

        if (parent && parent->getStmtClass() == clang::Stmt::StmtClass::IfStmtClass) {
            feature = "1";
        }
        else if (parent && parent->getStmtClass() == clang::Stmt::StmtClass::GotoStmtClass) {
            feature = "4";
        }
        else if (parent && parent->getStmtClass() == clang::Stmt::StmtClass::SwitchStmtClass) {
            feature = "2";
        }

        stmt = parent;
    }

    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
