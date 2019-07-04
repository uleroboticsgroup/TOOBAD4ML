#ifndef IO_STDOUTFORMAT_H
#define IO_STDOUTFORMAT_H

#include "IOutputFormatStrategy.h"

namespace TOOBAD4ML {

namespace IO {

class cSTDOutputFormatStrategy: 
    public IOutputFormatStrategy {

public:
    ~cSTDOutputFormatStrategy() {}
    bool Write(llvm::raw_ostream&, Descriptor);

};

} /* IO */

} /* TOOBAD4ML */

#endif