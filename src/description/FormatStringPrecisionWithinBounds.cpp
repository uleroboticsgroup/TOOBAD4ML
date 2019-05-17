#include "description/FormatStringPrecisionWithinBounds.h"
#include "description/BufferOverflow.h"

// ----------------------------------------------------------------------------

using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cFormatStringPrecisionWithinBounds::cFormatStringPrecisionWithinBounds(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

int  cFormatStringPrecisionWithinBounds::FormatStringParser(llvm::StringRef formatString, std::string function, clang::Expr* sink) {

		if(function.compare("scanf") == 0) {

			// [=%[*][width][modifiers]type=]

			std::vector<char> modifiers = {'c', 's', 'd', 'i', 'n', 'o', 'u', 'x', 'e', 'f', 'g'};

			std::string number = "";

			int limit = 0;

			for(llvm::StringRef::iterator it = formatString.begin(); it != formatString.end(); it++) {

				if((*it)=='%') {
					it++;
				}

				if((*it)=='*'){
					it++;
				}

				if(isdigit((*it))) {
					number.push_back((*it));
				}

				if(std::find(modifiers.begin(), modifiers.end(), (*it)) != modifiers.end()) {
					break;
				}
			}

			if(number.length() != 0)
				limit = std::stoi(number);

			return limit == 0 ? -1 : limit  ;

		}

		if(function.compare("sprintf") == 0) {

			// %[flags][width][.precision][length]specifier

			std::string number = "";
			int contChars = 0;
			int limit = 0;
			int width = 0;
			int precision = 0;
			int countArg = 0;
			int countSpecifierAlone = 0;

			for(llvm::StringRef::iterator it = formatString.begin(); it != formatString.end(); it++) {

				if((*it) != '%') {
					contChars++;
				} else {
					it++;
					while((*it) != 's' && (*it) != 'd' && it != formatString.end()) { // %...specifier
						if(isdigit(*it)) {
							number.push_back((*it));
						}
						else if((*it) == '.') {
							if(number.length() != 0)
							{
								width = std::stoi(number);
								number = "";
							}
						}
						if(it != formatString.end())
							it++;
					}

					if(number.length() != 0)
					{
						precision = std::stoi(number);
						number = "";
					}

					limit = limit + width + precision;

					if((*it) == 's' || (*it) == 'd') {
						countArg++;
						if(width+precision != 0) {
							countSpecifierAlone++;
							width = 0;
							precision = 0;
						}
					}

				}

			 }

			bool err = false;

			if (sink->getStmtClass()
					== clang::Stmt::StmtClass::CallExprClass) {

				clang::CallExpr* call = llvm::dyn_cast<clang::CallExpr>(sink);

				for(int i = (countArg - countSpecifierAlone); i<countArg; i++) {
					if(call->getNumArgs() >= (2 + countArg)){
						if (clang::Expr* s = call->getArg(2 + i)->IgnoreCasts()) {
							std::string name = s->getStmtClassName();
							if (name.compare("DeclRefExpr") == 0) {
								if(clang::DeclRefExpr *ref = llvm::dyn_cast<clang::DeclRefExpr>(s)) {
									if(clang::VarDecl* VD = llvm::dyn_cast_or_null<clang::VarDecl>(ref->getDecl())) {
										if(VD->hasInit()){

											if(clang::IntegerLiteral* intLiteral  = llvm::dyn_cast_or_null<clang::IntegerLiteral>(VD->getInit())) {
												int num = intLiteral->getValue().getLimitedValue();
												std::string n = std::to_string(num);
												int len = n.length();
												limit += len;
											}
											else if(clang::StringLiteral* intLiteral  = llvm::dyn_cast_or_null<clang::StringLiteral>(VD->getInit())) {
												clang::StringLiteral* strLiteral = llvm::dyn_cast<clang::StringLiteral>(s);
												if (auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(s->getType().getTypePtr())) {
													int destinationSize = t->getSize().getLimitedValue();
													limit += destinationSize;
												}
											}
											else {
												err = true;
												break;
											}
										}
									}
								}

							} else if (name.compare("StringLiteral") == 0) {

								clang::StringLiteral* strLiteral = llvm::dyn_cast<clang::StringLiteral>(s);

								if (auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(s->getType().getTypePtr())) {

									int destinationSize = t->getSize().getLimitedValue();
									limit += destinationSize;
								}
								else {
									err = true;
									break;
								}
							} else  if (name.compare("IntegerLiteral") == 0) {
								if(clang::IntegerLiteral* intLiteral  = llvm::dyn_cast_or_null<clang::IntegerLiteral>(s)) {
									int num = intLiteral->getValue().getLimitedValue();
									std::string n = std::to_string(num);
									int len = n.length();
									limit += len;
								}
								else {
									err = true;
									break;
								}

							}
						}
					}
				}

			}

			return 	( err ? (-1) : (limit + contChars));

			}

	return 0;
}

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cFormatStringPrecisionWithinBounds::ExtractFeature(
		cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg,
			bof);

	std::vector<llvm::StringRef> sinkTypes = { "scanf", "sscanf", "sprintf", "snprintf" };

	std::string feature = "-1";

	if (bof.GetSink()->getStmtClass()
			== clang::Stmt::StmtClass::CallExprClass && bof.GetBuffer() != nullptr) {

		clang::CallExpr* call = llvm::dyn_cast<clang::CallExpr>(bof.GetSink());

		if (std::find(sinkTypes.begin(), sinkTypes.end(),
				call->getDirectCallee()->getName()) != sinkTypes.end()) {

			// for the case of sprintf checks size of format string to be copied into buffer
			if (call->getDirectCallee()->getName() == "sprintf") {

				// buffer size
				unsigned destinationSize;
				if (auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(bof.GetBuffer()->getType().getTypePtr())) {

					destinationSize = t->getSize().getLimitedValue();

					//llvm::outs() << destinationSize << "\n";

					// get size of format buffer  ( 2 arg sprintf)
					if (clang::Expr* s = call->getArg(1)->IgnoreCasts()) {

						std::string name = s->getStmtClassName();

						if (name.compare("StringLiteral") == 0) {

							clang::StringLiteral* strLiteral = llvm::dyn_cast<clang::StringLiteral>(s);

							llvm::StringRef formatString = 	strLiteral->getString();

							int limit = cFormatStringPrecisionWithinBounds::FormatStringParser(formatString, "sprintf", bof.GetSink());

							if(limit != -1) {
								if (auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(bof.GetBuffer()->getType().getTypePtr())) {

									uint64_t destinationSize = t->getSize().getLimitedValue();

									if (limit != 0 && limit < destinationSize) { // null terminator included
										feature = "1";
									} else {
										feature = "0";
									}
								}
							} else {
								feature = "-1";
							}
						}
					}
				}

			} else if (call->getDirectCallee()->getName() == "snprintf") {

				if (clang::Expr* s = call->getArg(1)->IgnoreCasts()) {

					std::string name = s->getStmtClassName();

					if (name.compare("IntegerLiteral") == 0) {

						clang::IntegerLiteral* intLiteral = llvm::dyn_cast<clang::IntegerLiteral>(s);

						uint64_t limitSize = intLiteral->getValue().getLimitedValue();

						if (auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(bof.GetBuffer()->getType().getTypePtr())) {

							uint64_t destinationSize = t->getSize().getLimitedValue();

							if (limitSize < destinationSize) { // null terminator included
								feature = "1";
							} else {
								feature = "0";
							}
						}


					}
				}


			} else if (call->getDirectCallee()->getName() == "scanf") {


				if (clang::Expr* s = call->getArg(0)->IgnoreCasts()) {

					std::string name = s->getStmtClassName();

					if (name.compare("StringLiteral") == 0) {

						clang::StringLiteral* strLiteral = llvm::dyn_cast<clang::StringLiteral>(s);

						llvm::StringRef formatString =
								strLiteral->getString();

						int limit = cFormatStringPrecisionWithinBounds::FormatStringParser(formatString, "scanf", bof.GetSink());

						if(limit != -1) {
							if (auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(bof.GetBuffer()->getType().getTypePtr())) {

							uint64_t destinationSize = t->getSize().getLimitedValue();

							if (limit != 0 && limit < destinationSize) { // null terminator included
								feature = "1";
							} else {
								feature = "0";
							}
						} else {
							feature = "-1";
						}
					}

					}
				}



			}
			//TODO
			else if (call->getDirectCallee()->getName() == "sscanf") {





			}

		}

	} else {

		feature = "-1";
	}

	return decoratedFeature.append(feature).append(
			cDescriptorDecorator::FEATURE_SEPARATOR);
}
