#ifndef IO_FORMATSTRAT_H
#define IO_FORMATSTRAT_H
// ------------------------------------------------------------------------
#include <llvm/Support/raw_ostream.h>
// ------------------------------------------------------------------------
#include <iostream>
#include <vector>
// ------------------------------------------------------------------------

namespace TOOBAD4ML {
namespace IO {

// ------------------------------------------------------------------------
typedef std::vector<std::string> Descriptor;
// ------------------------------------------------------------------------

/*!
 * \class IOutputFormatStrategy
 *
 * \brief
 * An interface that holds an output strategy.
 *
 * */
class IOutputFormatStrategy {

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------
public:
    virtual ~IOutputFormatStrategy() {}

    // CLASS METHODS
    // ------------------------------------------------------------------------

public:
    virtual bool Write(llvm::raw_ostream&, Descriptor) = 0;
};

} /* IO */

} /* TOOBAD4ML */

#endif