#include "description/ConditionDepth.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cConditionDepth::cConditionDepth(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cConditionDepth::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    int feature = 0;

    clang::Expr* expr = bof.GetSink();
    const clang::Stmt* stmt = const_cast<clang::Stmt*>(llvm::dyn_cast<clang::Stmt>(expr));
    const clang::Stmt* parent;

    while(stmt) {
        const auto& parents = cpg.GetAST().getASTContext().getParents(*stmt);
        if (!parents.empty()) {
            parent = parents[0].get<clang::Stmt>();
        }

        if (parent && (parent->getStmtClass() == clang::Stmt::StmtClass::IfStmtClass ||
            parent->getStmtClass() == clang::Stmt::StmtClass::GotoStmtClass ||
            parent->getStmtClass() == clang::Stmt::StmtClass::SwitchStmtClass)){
                feature += 1;
            }

        stmt = parent;
    }

    return decoratedFeature.append(std::to_string(feature)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
