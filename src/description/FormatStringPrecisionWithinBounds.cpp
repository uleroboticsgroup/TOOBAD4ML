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

int  cFormatStringPrecisionWithinBounds::FormatStringParser(llvm::StringRef formatString, std::string function) {

		int limit = 0;

		std::vector<char> modifiers = {'c', 's', 'd', 'i', 'n', 'o', 'u', 'x', 'e', 'f', 'g'};


		if(function.compare("scanf") == 0) {

			// [=%[*][width][modifiers]type=]

			std::string number = "";

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

			limit = std::stoi(number);

		}




	return limit;
}

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cFormatStringPrecisionWithinBounds::ExtractFeature(
		cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg,
			bof);

	std::vector<llvm::StringRef> sinkTypes = { "scanf", "sscanf", "sprintf",
			"snprintf" };

	std::string feature = "-1";

	if (bof.GetSink()->getStmtClass()
			== clang::Stmt::StmtClass::CallExprClass) {

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

							clang::StringLiteral* strLiteral = llvm::dyn_cast<
									clang::StringLiteral>(s);

							llvm::StringRef formatString =
									strLiteral->getString();

							unsigned ret;
							unsigned size = destinationSize;
							std::string ss;

							for (int i = 0; i < destinationSize; i++) {
								ss.append("A");
							}

							//	llvm::outs() << ss << "\n";

							char *buffer = (char*) std::calloc(size + 1,
									sizeof(char));

							if (buffer == NULL) {
								/* Error al intentar reservar memoria */
							} else {

								if (call->getNumArgs() == 3) {

									ret = std::sprintf(buffer,
											formatString.str().c_str(),
											ss.c_str());

									//llvm::outs() << ret << "\n";
									//llvm::outs() << buffer << "\n";

									if (ret < size) { // null terminator included
										feature = "1";
									} else {
										feature = "0";
									}
								}

								free(buffer);

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

						int limit = cFormatStringPrecisionWithinBounds::FormatStringParser(formatString, "scanf");

						if (auto t = llvm::dyn_cast_or_null<clang::ConstantArrayType>(bof.GetBuffer()->getType().getTypePtr())) {

						uint64_t destinationSize = t->getSize().getLimitedValue();

						if (limit < destinationSize) { // null terminator included
							feature = "1";
						} else {
							feature = "0";
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
