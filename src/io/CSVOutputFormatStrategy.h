#ifndef IO_CSVOUTPUT_H
#define IO_CSVOUTPUT_H
#include "IOutputFormatStrategy.h"

namespace TOOBAD4ML {

namespace IO {

class cCSVOutputFormatStrategy
: public IOutputFormatStrategy {
public:
    ~cCSVOutputFormatStrategy() {}
    bool Write(llvm::raw_ostream&, Descriptor);
};

}

}
#endif