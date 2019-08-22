#ifndef IO_FSFACTORY_H_
#define IO_FSFACTORY_H_

#include <string>

namespace TOOBAD4ML {

namespace IO {

// CLASS FORWARDING
// ----------------------------------------------------------------------------
class IOutputFormatStrategy;

enum eOutputFormatType {
    CSV, 
    STD // Standard output
};

/*!
 * \class cFormatStrategyFactory
 *
 * \brief
 * A factory to produce the different type of output strategies.
 *
 * \details
 * This class is an implementation of the abstract factory pattern 
 * to generate the different types of strategies to produce the 
 * available outputs.
 * 
 * Currently it supports standard output and CSV output to file.
 */
class cFormatStrategyFactory {

    // CLASS METHODS
    // ------------------------------------------------------------------------
public:
    IOutputFormatStrategy& CreateCSVOutputFormatStrategy();
    IOutputFormatStrategy& CreateSTDOutputFormatStrategy();
    eOutputFormatType getOutputFormatType(std::string);
};

} /* IO */

} /* TOOBAD4ML */

#endif /* IO_FSFACTORY_H_ */
