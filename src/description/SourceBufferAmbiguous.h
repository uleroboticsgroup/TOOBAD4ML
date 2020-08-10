#ifndef TOOBAD4ML_DESCRIPTION_SOURCEBUFFERAMBIGUOUS_H_
#define TOOBAD4ML_DESCRIPTION_SOURCEBUFFERAMBIGUOUS_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cSourceBufferAmbiguous
 *
 * \brief
 * F69 If source buffer is ambiguous
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * It checks wether the source buffer is ambiguous. In this context, ambiguous means that at least 2 writes
 * are performed over the source buffer, one of them being made by some input and the other by the user input.
 * 
 */
class cSourceBufferAmbiguous: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSourceBufferAmbiguous(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cSourceBufferAmbiguous */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_SOURCEBUFFERAMBIGUOUS_H_ */
