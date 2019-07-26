#include "description/FormatStringPrecisionWithinBounds.h"
#include "description/BufferOverflow.h"
#include <string>
#include <iostream>
// ----------------------------------------------------------------------------

using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cFormatStringPrecisionWithinBounds::cFormatStringPrecisionWithinBounds(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

int cFormatStringPrecisionWithinBounds::getSprintfWriteSize(std::string formatString, clang::Expr* sink) {
	// %[flags][width][.precision][length]specifier
	std::vector<char> modifiers = {'c', 's', 'd', 'i', 'n', 'o', 'u', 'x', 'e', 'f', 'g', 'X', 'F', 'E', 'G', 'a', 'A', 'p'};
	std::string currentValue = "0"; // Width or precission
	int size = 0;
	int width = 0;
	int nArguments = 0;
	bool isFormatMode = false;
	bool hashtag = false;
	bool flagSet = false;
	char prevChar = '\0';

	// Obtain the format expression information
	for(std::string::iterator it = formatString.begin(); it != formatString.end(); it++) {
		char currentChar = *it;
		// Check if we begin the format expression
		if (currentChar != '%' && prevChar == '%') {
			// %% second 
			isFormatMode = true;
		}

		if (isFormatMode) {
			switch (currentChar) {
				case ' ':
				case '+': 
					if (!flagSet) {
						// Because only one can appear
						size++;
						flagSet = true;
					}
					break;

				case '#': 
					hashtag = true;
					flagSet = true;
					break;

				case '.': {
					// Precission field begins
					width = std::stoi(currentValue);
					currentValue = "0";
				}
					break;
				
				case '*': {
					// We need the arguments
				}
				break;
			}

			if (isdigit(currentChar)) {
				currentValue += currentChar;
			}

			// End of format expression?
			if (std::find(modifiers.begin(), modifiers.end(), currentChar) != modifiers.end()) {
				if (hashtag) {
					switch (currentChar) {
					case '0':
						size += 1;
						break;

					case 'x':
					case 'X':
						size += 2;
						break;
					}
				}

				if (std::stoi(currentValue) > width) {
					width = std::stoi(currentValue);
				}

				size += width;
				nArguments++;
				hashtag = false;
				flagSet = false;
				isFormatMode = false;
			}
		}
		else {
			size++; // Regular character
		}

		prevChar = currentChar;
	}
	
	// Calculate how much does the arguments to be passed to the expression occupy
	if (sink->getStmtClass() == clang::Stmt::StmtClass::CallExprClass) {
		clang::CallExpr* sinkCallExpr = llvm::dyn_cast<clang::CallExpr>(sink);

		if (sinkCallExpr->getNumArgs() != (2 + nArguments)) {
			return -1;
		}

		for (int i = 2; i < (2 + nArguments); i++) {

			clang::Expr* argExpr = sinkCallExpr->getArg(i)->IgnoreCasts();
			

			switch (argExpr->getStmtClass()) {

				case clang::Stmt::StmtClass::DeclRefExprClass: {
					clang::DeclRefExpr* argDeclRefExpr = llvm::dyn_cast<clang::DeclRefExpr>(argExpr);

					// What else should we expect to find ??
					clang::VarDecl* VD = llvm::dyn_cast_or_null<clang::VarDecl>(argDeclRefExpr->getDecl());

					if(VD->hasInit()){
						
						switch(VD->getInit()->getStmtClass()) {
							case clang::Stmt::StmtClass::StringLiteralClass: {
								clang::StringLiteral* argStrLiteral = llvm::dyn_cast<clang::StringLiteral>(VD->getInit());

								size += argStrLiteral->getLength();
							}
							break;

							case clang::Stmt::StmtClass::IntegerLiteralClass: {
								clang::IntegerLiteral* argIntLiteral  = llvm::dyn_cast_or_null<clang::IntegerLiteral>(VD->getInit());

								int argValue = argIntLiteral->getValue().getLimitedValue();
								size += std::to_string(argValue).length();
							}
							break;


						}
					}
				}
				break;

				case clang::Stmt::StmtClass::StringLiteralClass: {
					clang::StringLiteral* argStringLiteral = llvm::dyn_cast<clang::StringLiteral>(argExpr);

					size += argStringLiteral->getLength();
				}
				break;

				case clang::Stmt::StmtClass::IntegerLiteralClass: {
					clang::IntegerLiteral* argIntegerLiteral = llvm::dyn_cast_or_null<clang::IntegerLiteral>(argExpr);

					int argValue = argIntegerLiteral->getValue().getLimitedValue();
					size += std::to_string(argValue).length();
				}
				break;

			}
		}
	}

	return size == 0 ? -1 : size;
}

int cFormatStringPrecisionWithinBounds::getScanfSize(std::string formatString) {
	// %[*][width][length]specifier 

	std::vector<char> modifiers = {'c', 's', 'd', 'i', 'n', 'o', 'u', 'x', 'e', 'f', 'g', 'p', '['};
	std::string size = "0";
	char currentChar = '\0'; 
	int limit = 0;

	for(std::string::iterator it = formatString.begin(); it != formatString.end(); it++) {
		currentChar = *it;

		if (currentChar == '*') {
			// Nothing is going to be written in the buffer
			return INT_MAX;
		}

		if (isdigit(currentChar)) {
			size.push_back(currentChar);
		}

		if(std::find(modifiers.begin(), modifiers.end(), currentChar) != modifiers.end()) {
			// Anything from here is ignored.
			break;
		}
	}

	limit = std::stoi(size);
	return limit == 0 ? -1 : limit;
	
}

int cFormatStringPrecisionWithinBounds::FormatStringParser(std::string formatString, std::string functionName, clang::Expr* sink) {

	if(functionName == "scanf") {
		return getScanfSize(formatString);
	}
	else if(functionName == "sprintf") {
		return getSprintfWriteSize(formatString, sink);
	}

	return 0;
}

// INHERITED METHODS
// ----------------------------------------------------------------------------
std::string cFormatStringPrecisionWithinBounds::ExtractFeature(
		cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(cpg,
			bof);

	std::vector<std::string> sinkTypes = { "scanf", "sscanf", "sprintf", "snprintf" };

	std::string feature = "-1";

	if (bof.GetSink()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass && 
		bof.GetBuffer() != nullptr) {
		
		// SAME PROBLEM OF ALWAYS - We need the size of the buffer.
		clang::CallExpr* call = llvm::dyn_cast<clang::CallExpr>(bof.GetSink());

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

							std::string formatString = 	strLiteral->getString();

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

						std::string formatString =
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

	} else {

		feature = "-1";
	}

	return decoratedFeature.append(feature).append(
			cDescriptorDecorator::FEATURE_SEPARATOR);
}
