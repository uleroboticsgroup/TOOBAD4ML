#include "description/DestinationBufferPredicates.h"
#include "description/BufferOverflow.h"
#include "description/CodePropertyGraph.h"
#include "description/ExprUtils.h"
#include "ASTTraversal/FindVariableVisitor.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTOR
// ------------------------------------------------------------------------
cDestinationBufferPredicates::cDestinationBufferPredicates(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ------------------------------------------------------------------------
std::string cDestinationBufferPredicates::ExtractFeature(cCodePropertyGraph& cpg, cBufferOverflow& bof) {
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg, bof);
    int feature = 0;

    cExprUtils* exprUtils = cExprUtils::GetInstance();
    SinkPathGraph spg = cpg.GetSPG(*(bof.GetSink()));
    clang::DeclRefExpr* dstBuffer = bof.GetBuffer(BufferType::DST);

    if(dstBuffer){
        for(clang::CFGStmt cfgStmt: spg) {
    		clang::Stmt* stmt = const_cast<clang::Stmt*>(cfgStmt.getStmt());

            ASTTraversal::cFindVariableVisitor dstVisitor(dstBuffer);
            dstVisitor.TraverseStmt(stmt);

            if (dstVisitor.IsFound()) {
                feature += 1;
            } 
       }
    }

    return decoratedFeature.append(std::to_string(feature)).append(cDescriptorDecorator::FEATURE_SEPARATOR);    
}
