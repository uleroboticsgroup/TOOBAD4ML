//---------
#ifndef TOOBAD4ML_DESCRIPTION_BUFFEROVERFLOWBUILDER_H
#define TOOBAD4ML_DESCRIPTION_BUFFEROVERFLOWBUILDER_H
// ----------------------------------------------------------------------------
#include <clang/AST/Expr.h>
#include "description/CodePropertyGraph.h"
// ----------------------------------------------------------------------------

namespace TOOBAD4ML {

namespace description {
// ----------------------------------------------------------------------------
class cBufferOverflow;
class cCodePropertyGraph;
// ----------------------------------------------------------------------------

class cBufferOverflowBuilder {

public:
    cBufferOverflow& CreateBufferOverflow(clang::Expr&, cCodePropertyGraph&);

private:
    std::vector<clang::CallExpr*> getInputs(clang::DeclRefExpr&, SinkPathGraph);
    clang::DeclRefExpr* getBuffer(clang::Expr&);
};

}

}

#endif