#ifndef TOOBAD4ML_DESCRIPTION_COMMANDLINE_H_
#define TOOBAD4ML_DESCRIPTION_COMMANDLINE_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cCommandLine: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 */
	cCommandLine(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

}; /* cCommandLine */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_COMMANDLINE_H_ */
