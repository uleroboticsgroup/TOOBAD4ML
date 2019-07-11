#ifndef IO_STDOUTFORMAT_H
#define IO_STDOUTFORMAT_H

#include "IOutputFormatStrategy.h"

namespace TOOBAD4ML {

namespace IO {

/*!
 * \class cSTDOutputFormatStrategy
 *
 * \brief
 * An implementation of IOutputFormatStrategy to write the output to standard output.
 *
 */
class cSTDOutputFormatStrategy: 
    public IOutputFormatStrategy {

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------

public:
    ~cSTDOutputFormatStrategy() {}

    // INHERITED METHODS
    // ------------------------------------------------------------------------
public:
    bool Write(llvm::raw_ostream&, Descriptor);

};

} /* IO */

} /* TOOBAD4ML */

#endif