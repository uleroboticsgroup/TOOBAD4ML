#ifndef TOOBAD4ML_DESCRIPTION_DESTINATIONWRITES_H_
#define TOOBAD4ML_DESCRIPTION_DESTINATIONWRITES_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cDestinationWrites
 *
 * \brief
 * F58 Multiple writes destination
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * It checks wether there are more writes to the destination
 * buffer than the one in the sink.
 * 
 * 0: false
 * 1: true
 *
 */
class cDestinationWrites: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cDestinationWrites(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cDestinationWrites */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_DESTINATIONWRITES_H_ */
