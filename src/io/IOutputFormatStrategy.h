#ifndef IO_FORMATSTRAT_H
#define IO_FORMATSTRAT_H

#include <llvm/Support/raw_ostream.h>

namespace TOOBAD4ML {

namespace IO {

typedef std::vector<std::string> Descriptor;

class IOutputFormatStrategy {
public:
    virtual ~IOutputFormatStrategy() {}
    virtual bool Write(llvm::raw_ostream&, Descriptor) = 0;
};

}

}
#endif