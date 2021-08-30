#include "io/FunctionTypeTranslator.h"

using namespace TOOBAD4ML;
using namespace IO;

/*
cFunctionTypeTranslator::cFunctionTypeTranslator(){

}

cFunctionTypeTranslator::~cFunctionTypeTranslator(){

}
*/

int cFunctionTypeTranslator::GetDstBufferPos(const llvm::Twine function){

	//TODO YET TO BE IMPLEMENTED
	/*
	 * Some sort of map/dictionary that tells us what the position
	 * of the buffer is within function body
	 */

	return 0;
}

eVulnerableFunctionType cFunctionTypeTranslator::GetFuncType(const llvm::Twine function){

	//TODO YET TO BE IMPLEMENTED

	return eVulnerableFunctionType::STR_COPY;
}

eInputFunctionType cFunctionTypeTranslator::GetInputFuncType(){

	//TODO YET TO BE IMPLEMENTED

	return eInputFunctionType::CMD_LINE;
}

//TODO YET TO BE IMPLEMENTED
	/*
	 * IF INSTANCE DOES NOT EXIST -> CREATE AND RETURN (calling constructor)
	 * OTHERWISE -> RETURN ALREADY EXISTING INSTANCE

static cFunctionTypeTranslator* cFunctionTypeTranslator::GetInstance(){



}
*/
