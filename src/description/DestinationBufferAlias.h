#ifndef TOOBAD4ML_DESCRIPTION_DESTINATIONBUFFERALIAS_H_
#define TOOBAD4ML_DESCRIPTION_DESTINATIONBUFFERALIAS_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cDestinationBufferAlias
 *
 * \brief
 * F17. Whether there is an alias for the destination buffer
 *
 * \details
 *  This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 *  and it's an implementation of the Decorator pattern.
 * 
 *  Whether there is an alias for the destination buffer
 * 
 *  0: False
 *  1: True 
 *
 */
class cDestinationBufferAlias: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cDestinationBufferAlias(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cDestinationBufferAlias */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_DESTINATIONBUFFERALIAS_H_ */
