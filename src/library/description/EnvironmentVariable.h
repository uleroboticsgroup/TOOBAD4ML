#ifndef TOOBAD4ML_DESCRIPTION_ENVIRONMENT_H_
#define TOOBAD4ML_DESCRIPTION_ENVIRONMENT_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cEnvironmentVariable
 *
 * \brief
 * Input Classification. Classifies the inputs as Environment Variable type
 *
 * \details
 * Count the number of nodes Environment Variable (e.g., getwd, getcwd) based
 * on nature input source. Uses sink's control as well as data dependencies
 * for identifying sink input sources.  It is imperative to classify sink input
 * sources because certain type of input validation is only relevant for
 * particular input types (for example EOF check for data read from files).
 *
 */
class cEnvironmentVariable: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cEnvironmentVariable(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

} /* description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_ENVIRONMENT_H_ */
