#ifndef TOOBAD4ML_DESCRIPTION_DESTINATIONBUFFERAMBIGUOUS_H_
#define TOOBAD4ML_DESCRIPTION_DESTINATIONBUFFERAMBIGUOUS_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cDestinationBufferAmbiguous
 *
 * \brief
 * F68 If destination buffer is ambiguous
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * It checks wether the destination buffer is ambiguous. In this context, ambiguous means that at least 2 writes
 * are performed over the destination buffer, one of them being made by some input and the other by the user input.
 * 
 */
class cDestinationBufferAmbiguous: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cDestinationBufferAmbiguous(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cDestinationBufferAmbiguous */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_DESTINATIONBUFFERAMBIGUOUS_H_ */
