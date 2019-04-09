#ifndef TOOBAD4ML_DESCRIPTION_ENVIRONMENT_H_
#define TOOBAD4ML_DESCRIPTION_ENVIRONMENT_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cEnvironmentVariable: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 */
	cEnvironmentVariable(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

} /* description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_ENVIRONMENT_H_ */
