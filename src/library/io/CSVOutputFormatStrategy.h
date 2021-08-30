#ifndef IO_CSVOUTPUT_H
#define IO_CSVOUTPUT_H
// ------------------------------------------------------------------------
#include "IOutputFormatStrategy.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace IO {

/*!
 * \class cCSVOutputFormatStrategy
 *
 * \brief
 * An implementation of IOutputFormatStrategy to write the output to file in CSV format.
 *
 */
class cCSVOutputFormatStrategy
: public IOutputFormatStrategy {

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------
public:
    ~cCSVOutputFormatStrategy() {}

    // INHERITED METHODS
    // ------------------------------------------------------------------------
public:
    bool Write(llvm::raw_ostream&, Descriptor);
};

}

}
#endif