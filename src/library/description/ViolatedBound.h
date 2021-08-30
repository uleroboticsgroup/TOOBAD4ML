#ifndef TOOBAD4ML_DESCRIPTION_VIOLATEDBOUND_H_
#define TOOBAD4ML_DESCRIPTION_VIOLATEDBOUND_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cViolatedBound
 *
 * \brief
 * F13. Indicates which end of the destination buffer has been violated
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * Indicates which end of the destination buffer has been violated
 * 
 * -1 - Unknown
 *  0 - Lower
 *  1 - Upper
 *
 */
class cViolatedBound: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cViolatedBound(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cViolatedBound */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_VIOLATEDBOUND_H_ */
