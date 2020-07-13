#ifndef TOOBAD4ML_DESCRIPTION_MAGNITUDE_H_
#define TOOBAD4ML_DESCRIPTION_MAGNITUDE_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cMagnitude
 *
 * \brief
 * F26. Size of the buffer overflow
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * Size of the buffer overflow in bytes
 *
 */
class cMagnitude: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cMagnitude(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cMagnitude */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_MAGNITUDE_H_ */
