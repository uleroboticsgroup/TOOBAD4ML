#include "io/FormatStrategyFactory.h"
#include "io/CSVOutputFormatStrategy.h"
#include "io/STDOutputFormatStrategy.h"
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace IO;

// CLASS METHODS
// ------------------------------------------------------------------------
IOutputFormatStrategy& cFormatStrategyFactory::CreateCSVOutputFormatStrategy() {
    return *(new cCSVOutputFormatStrategy());
}

IOutputFormatStrategy& cFormatStrategyFactory::CreateSTDOutputFormatStrategy() {
    return *(new cSTDOutputFormatStrategy());
}

eOutputFormatType cFormatStrategyFactory::getOutputFormatType(std::string type) {
    if (type == "CSV") {
        return eOutputFormatType::CSV;
    }
    else {
        return eOutputFormatType::STD;
    }
}
