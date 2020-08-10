#ifndef TOOBAD4ML_DESCRIPTION_DESTINATIONBUFFERPREDICATES_H_
#define TOOBAD4ML_DESCRIPTION_DESTINATIONBUFFERPREDICATES_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cDestinationBufferPredicates
 *
 * \brief
 * F65 Counts the number of sink predicates which are directly or transitively dependent on the destination buffer
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * Counts the number of sink predicates which are directly or transitively dependent on 
 * buffer defined at k and helps to infer on checks performed on destination
 * 
 */
class cDestinationBufferPredicates: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cDestinationBufferPredicates(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cDestinationBufferPredicates */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_DESTINATIONBUFFERPREDICATES_H_ */
