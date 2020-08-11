#include "description/SecondaryControlFlow.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
#include "ASTTraversal/FindVariableVisitor.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cSecondaryControlFlow::cSecondaryControlFlow(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cSecondaryControlFlow::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    std::string feature = "0";
    bool firstControlFlow = true;

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
            if (firstControlFlow){
                firstControlFlow = false;
            }
            else {
                feature = "1";
            }
        }
        else if (parent && parent->getStmtClass() == clang::Stmt::StmtClass::GotoStmtClass) {
            if (firstControlFlow){
                firstControlFlow = false;
            }
            else {
                feature = "4";
            }
        }
        else if (parent && parent->getStmtClass() == clang::Stmt::StmtClass::SwitchStmtClass) {
            if (firstControlFlow){
                firstControlFlow = false;
            }
            else {
                feature = "2";
            }
        }

        stmt = parent;
    }

    return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
