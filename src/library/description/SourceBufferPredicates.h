#ifndef TOOBAD4ML_DESCRIPTION_SOURCEBUFFERPREDICATES_H_
#define TOOBAD4ML_DESCRIPTION_SOURCEBUFFERPREDICATES_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cSourceBufferPredicates
 *
 * \brief
 * F64. Counts the number of source inputs validation
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * Counts the number of source inputs validation
 * 
 */
class cSourceBufferPredicates: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSourceBufferPredicates(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cSourceBufferPredicates */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_VIOLATEDBOUND_H_ */
