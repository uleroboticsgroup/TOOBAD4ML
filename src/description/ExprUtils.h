#ifndef DESCRIPTION_EXPRUTILS
#define DESCRIPTION_EXPRUTILS
#include "clang/AST/ASTContext.h"
#include "clang/AST/Expr.h"

namespace TOOBAD4ML {

namespace description {

class cExprUtils {

    // CLASS METHODS
    // ------------------------------------------------------------------------
public:
    static cExprUtils* GetInstance();
    int guessBufferSize(clang::DeclRefExpr* buffer, clang::ASTContext& context);
    int guessArgumentSize(clang::Expr* arg, clang::ASTContext& context);
    clang::ValueDecl* getValueFromDeclRefExpr(clang::Expr*);
    int getValueFromIntegerLiteral(clang::Expr*);
    clang::Expr* getExprFromUnaryOperator(clang::Expr*);
    clang::Expr* getIndexFromArraySubscriptExpr(clang::Expr*);
    clang::DeclRefExpr* getArrayFromArraySubscriptExpr(clang::Expr*);

private:
    cExprUtils() {};

    // ATTRIBUTES
    // ------------------------------------------------------------------------
private:
    static std::unique_ptr<cExprUtils> m_instance;
};

}

}

#endif