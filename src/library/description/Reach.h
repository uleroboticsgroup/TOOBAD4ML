#ifndef TOOBAD4ML_DESCRIPTION_REACH_H_
#define TOOBAD4ML_DESCRIPTION_REACH_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cReach
 *
 * \brief
 * F28. Indicates whether the access violation was preceded by consecutive access of elements starting within 
 * the array or just an access outside of the buffer
 *
 * \details
 *  This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 *  and it's an implementation of the Decorator pattern.
 * 
 *  Indicates whether the access violation was preceded by consecutive access of elements starting within 
 * the array or just an access outside of the buffer
 * 
 * - Not applicable:      -1
 * - Consecutive access:   0
 * - Access outside:       1
 *
 */
class cReach: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cReach(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cReach */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_REACH_H_ */
