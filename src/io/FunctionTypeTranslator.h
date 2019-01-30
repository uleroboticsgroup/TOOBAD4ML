#ifndef IO_FUNCTIONTYPETRANSLATOR_H_
#define IO_FUNCTIONTYPETRANSLATOR_H_

#include "llvm/ADT/Twine.h"

namespace TOOBAD4ML {

namespace io {

enum class eVulnerableFunctionType {
	STR_COPY = 1,
	STR_CONCAT,
	MEM_ALTERATION,
	FORMAT_STR_OUTPUT,
	UNFORMAT_STR_INPUT,
	FORMAT_STR_INPUT,
	NOT_VALID = -1
};

enum class eInputFunctionType {
	CMD_LINE = 1,
	ENV_VAR,
	FILE,
	NETWORK,
	NOT_VALID = -1
};

struct FunctionData{
	int m_dstBufferPost;
	eVulnerableFunctionType m_funcType;
	eInputFunctionType m_inputFuncType;
};

class cFunctionTypeTranslator {

public:

	int GetDstBufferPos(const llvm::Twine);

	eVulnerableFunctionType GetFuncType(const llvm::Twine);

	eInputFunctionType GetInputFuncType();

	//static cFunctionTypeTranslator* GetInstance();

private:

	//cFunctionTypeTranslator();

	//std::map<llvm::StringRef, FunctionData> m_functions;

	std::unique_ptr<cFunctionTypeTranslator> m_instance;

	//~cFunctionTypeTranslator();
};



}
}

#endif /* IO_FUNCTIONTYPETRANSLATOR_H_ */
