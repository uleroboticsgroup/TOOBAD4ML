#ifndef TOOBAD4ML_DESCRIPTION_HASDEFENSIVELIMITS_H_
#define TOOBAD4ML_DESCRIPTION_HASDEFENSIVELIMITS_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cHasDefensiveLimits
 *
 * \brief
 * F56. Flags the usage of secure versions of C library functions where number of elements for filling destina-
tion is specified in the sink statement
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * This attribute is used to flag usage of secure versions of C library functions where number of elements for filling destination is specified in the sink statement (e.g., strncpy, snprintf)
 * 
 * -1: Not applicable
 *  0: False (it doesn't use)
 *  1: True (it uses)
 *
 */
class cHasDefensiveLimits: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cHasDefensiveLimits(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cHasDefensiveLimits */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_HASDEFENSIVELIMITS_H_ */
