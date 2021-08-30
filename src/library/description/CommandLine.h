#ifndef TOOBAD4ML_DESCRIPTION_COMMANDLINE_H_
#define TOOBAD4ML_DESCRIPTION_COMMANDLINE_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cCommandLine
 *
 * \brief
 * Input Classification. Classifies the inputs as Command Line type
 *
 * \details
 * Count the number of nodes Command Line (e.g., scanf, gets) based
 * on nature input source. Uses sink's control as well as data dependencies
 * for identifying sink input sources.  It is imperative to classify sink input
 * sources because certain type of input validation is only relevant for
 * particular input types (for example EOF check for data read from files).
 *
 */
class cCommandLine: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cCommandLine(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

}; /* cCommandLine */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_COMMANDLINE_H_ */
