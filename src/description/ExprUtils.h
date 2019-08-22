#ifndef DESCRIPTION_EXPRUTILS
#define DESCRIPTION_EXPRUTILS
// ------------------------------------------------------------------------
#include "clang/AST/ASTContext.h"
#include "clang/AST/Expr.h"
#include "clang/AST/Stmt.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {
// ------------------------------------------------------------------------
/*!
 * \class cExprUtils
 *
 * \brief
 * This utility provides useful functions related to <CODE>clang::Expr</CODE> 
 *
 * \details
 * This class is a singleton which provides us a lot of useful functions to
 * be used with <CODE>clang::Expr</CODE> and all the ones that inherit from it.
 * The functions mainly provide ways to obtain what's inside of the parameters.
 *
 */
class cExprUtils {

    // CLASS METHODS
    // ------------------------------------------------------------------------
public:
    /*!
     * Obtains an instance of the singleton, creating it if necessary.
     *
     * @returns The singleton instance.
     */
    static cExprUtils* GetInstance();

    /*!
     * This functions obtains the size of a buffer.
     *
     * @param buffer The buffer itself
     * @param context The context where the buffer is.
     * @returns The size of the buffer.
     */
    int guessBufferSize(clang::DeclRefExpr*, clang::ASTContext&);

    /*!
     * Given an argument of a function, guess the size (buffer) or value.
     *
     * @param arg The argument
     * @param arg The context where the argument is
     * @returns The size or value of the argument
     */
    int guessArgumentSize(clang::Expr* arg, clang::ASTContext& context);

    /*!
     * Obtains the <CODE>clang::ValueDecl</CODE> inside a <CODE>clang::DeclRefExpr</CODE>
     *
     * @param expr The <CODE>clang::DeclRefExpr</CODE> containing the <CODE>clang::ValueDecl</CODE>
     * @returns The <CODE>clang::ValueDecl</CODE>
     */
    clang::ValueDecl* getValueFromDeclRefExpr(clang::Expr*);

    /*!
     * Obtains the int representation of a <CODE>clang::IntegerLiteral</CODE>
     *
     * @param expr The <CODE>clang::IntegerLiteral</CODE>
     * @returns The int value
     */
    int getValueFromIntegerLiteral(clang::Expr*);

    /*!
     * Obtains the <CODE>clang::Expr</CODE> which is inside of a <CODE>clang::UnaryOperator</CODE>
     *
     * @param expr The <CODE>clang::UnaryOperator</CODE>
     * @returns The <CODE>clang::Expr</CODE>
     */
    clang::Expr* getExprFromUnaryOperator(clang::Expr*);

    /*!
     * Obtains the <CODE>clang::Expr</CODE> representing
     * what it's insde the brackets ([]) of an <CODE>clang::ArraySubscriptExpr</CODE>
     *
     * @param expr The <CODE>clang::ArraySubscriptExpr</CODE>
     * @returns The <CODE>clang::Expr</CODE> of what's inside the brackets
     */
    clang::Expr* getIndexFromArraySubscriptExpr(clang::Expr*);

    /*!
     * Obtains the <CODE>clang::DeclRefExpr</CODE>, the array, from an <CODE>clang::ArraySubscriptExpr</CODE>
     *
     * @param expr The <CODE>clang::ArraySubscriptExpr</CODE>
     * @returns The <CODE>clang::DeclRefExpr</CODE> 
     */
    clang::DeclRefExpr* getArrayFromArraySubscriptExpr(clang::Expr*);

    /*!
     * Retrieve the <CODE>clang::Expr</CODE> from inside a <CODE>clang::BinaryOperator</CODE> 
     * which belongs to the given <CODE>clang::Stmt::StmtClass</CODE>
     * or return nullptr if it isn't found.
     *
     * @param binaryOperator The <CODE>clang::BinaryOperator</CODE>
     * @param targetClass The <CODE>clang::Stmt::StmtClass</CODE> we are looking for.
     * @returns The <CODE>clang::DeclRefExpr</CODE> (array)
     */
    std::vector<clang::Expr*> getFromComparisonBinaryOperator(clang::BinaryOperator*, clang::Stmt::StmtClass);

private:
    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------
    cExprUtils() {};

    // ATTRIBUTES
    // ------------------------------------------------------------------------
private:
    //! The singleton instance
    static std::unique_ptr<cExprUtils> m_instance;
};

}

}

#endif