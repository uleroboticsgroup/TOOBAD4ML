#ifndef IO_FSFACTORY_H_
#define IO_FSFACTORY_H_

#include <iostream>
#include <map>

namespace TOOBAD4ML {

namespace IO {

class IOutputFormatStrategy;

enum eOutputFormatType {
    CSV, 
    STD // Standard output
};

class cFormatStrategyFactory {
public:
    IOutputFormatStrategy& CreateCSVOutputFormatStrategy();
    IOutputFormatStrategy& CreateSTDOutputFormatStrategy();
    eOutputFormatType getOutputFormatType(std::string);

private:
    std::map<std::string, eOutputFormatType> m_enumTranslator;
};

}

}

#endif /* IO_FSFACTORY_H_ */
