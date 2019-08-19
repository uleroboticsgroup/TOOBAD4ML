#include "description/ExprUtils.h"
using namespace TOOBAD4ML;
using namespace description;

std::unique_ptr<cExprUtils> cExprUtils::m_instance = 0;

cExprUtils* cExprUtils::GetInstance() {
    if (!m_instance) {
        m_instance = std::unique_ptr<cExprUtils>(new cExprUtils());
    }

    return m_instance.get();
}

int cExprUtils::guessBufferSize(clang::DeclRefExpr* buffer, clang::ASTContext& context) {
	int size = -1;
	clang::Type* bufferTypePtr = const_cast<clang::Type*>(buffer->getType().getTypePtr());
	clang::Type::TypeClass bufferTypeClass = bufferTypePtr->getTypeClass();

	switch(bufferTypeClass) {
		case clang::Type::TypeClass::ConstantArray: {
			clang::ConstantArrayType* bufferConstArrayType = llvm::dyn_cast_or_null<clang::ConstantArrayType>(bufferTypePtr);
			size = bufferConstArrayType->getSize().getLimitedValue();
		}
		break;

		case clang::Type::TypeClass::IncompleteArray: {
			// Array has an unspecified size.
		}
		break;

		case clang::Type::TypeClass::VariableArray: {
			clang::VariableArrayType* bufferVariableArrayType = llvm::dyn_cast_or_null<clang::VariableArrayType>(bufferTypePtr);
			
			// ???
		}
		break;
		
		case clang::Type::TypeClass::DependentSizedArray: {
			clang::DependentSizedArrayType* bufferDependentSizedArrayType = llvm::dyn_cast_or_null<clang::DependentSizedArrayType>(bufferTypePtr);
			// ???
		}
		break;

		case clang::Type::TypeClass::Pointer: {
			// TODO not evaluable ?? Expr::tryEvaluateObjectSize -- TypeInfo -- ASTContext
		}
		break;
	}

	return size;
}

int cExprUtils::guessArgumentSize(clang::Expr* arg, clang::ASTContext& context) {
	int limit = -1;

	switch (arg->getStmtClass()) {
		case clang::Stmt::StmtClass::IntegerLiteralClass: {
			clang::IntegerLiteral* limitIntLiteral = llvm::dyn_cast<clang::IntegerLiteral>(arg);

			limit = limitIntLiteral->getValue().getLimitedValue();
		}
		break;

		case clang::Stmt::StmtClass::UnaryExprOrTypeTraitExprClass: {
			clang::UnaryExprOrTypeTraitExpr* sizeOfExpr = llvm::dyn_cast<clang::UnaryExprOrTypeTraitExpr>(arg);
			
			// SIZEOF 
			if(sizeOfExpr->isArgumentType()) {
				limit = context.getTypeSize(sizeOfExpr->getArgumentType());
			}
			else {
				clang::Expr* argumentExpr = sizeOfExpr->getArgumentExpr()->IgnoreParens();

				if (argumentExpr->getStmtClass() == clang::Stmt::StmtClass::DeclRefExprClass || 
					argumentExpr->getStmtClass() == clang::Stmt::StmtClass::BinaryOperatorClass) {
					limit = context.getTypeSize(argumentExpr->getType());
				}
			}
		}
		break;
		
		case clang::Stmt::StmtClass::DeclRefExprClass: {
			clang::DeclRefExpr* argDeclRefExpr = llvm::dyn_cast<clang::DeclRefExpr>(arg);

			switch (argDeclRefExpr->getType().getTypePtr()->getTypeClass()) {
				case clang::Type::TypeClass::Atomic:
				case clang::Type::TypeClass::Builtin: {
				}
				break;
				case clang::Type::TypeClass::IncompleteArray:
				case clang::Type::TypeClass::ConstantArray:
				case clang::Type::TypeClass::VariableArray:
				case clang::Type::TypeClass::DependentSizedArray: {
					limit = guessBufferSize(argDeclRefExpr, context);
				}
			}
		}
		break;

		case clang::Stmt::StmtClass::CallExprClass: {
			// Cannot be evaluated because of the constraint of the scope
		}
		break;
	}

	return limit;
}

clang::Expr* cExprUtils::getExprFromUnaryOperator(clang::Expr* expr) {
	return llvm::dyn_cast<clang::UnaryOperator>(expr->IgnoreCasts())->getSubExpr()->IgnoreCasts()->IgnoreParens(); 
}

clang::ValueDecl* cExprUtils::getValueFromDeclRefExpr(clang::Expr* expr) {
    return llvm::dyn_cast<clang::DeclRefExpr>(expr->IgnoreCasts())->getDecl();
}

int cExprUtils::getValueFromIntegerLiteral(clang::Expr* expr) {
    return llvm::dyn_cast_or_null<clang::IntegerLiteral>(expr)->getValue().getLimitedValue();
}

clang::Expr* cExprUtils::getIndexFromArraySubscriptExpr(clang::Expr* expr) {
	return llvm::dyn_cast_or_null<clang::ArraySubscriptExpr>(expr)->getIdx();
}

clang::DeclRefExpr* cExprUtils::getArrayFromArraySubscriptExpr(clang::Expr* expr) {
	return llvm::dyn_cast_or_null<clang::DeclRefExpr>(llvm::dyn_cast_or_null<clang::ArraySubscriptExpr>(expr)->getLHS()->IgnoreCasts()->IgnoreParens());
}