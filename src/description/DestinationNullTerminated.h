#ifndef TOOBAD4ML_DESCRIPTION_DESTINATIONNULLTERMINATED_H_
#define TOOBAD4ML_DESCRIPTION_DESTINATIONNULLTERMINATED_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cDestinationNullTerminated
 *
 * \brief
 * F57. Whether the destination buffer is null terminated at least once in the program
 *
 * \details
 *  This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 *  and it's an implementation of the Decorator pattern.
 * 
 *  Whether the destination buffer is null terminated at least once in the program
 * 
 *  0: False
 *  1: True 
 *
 */
class cDestinationNullTerminated: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cDestinationNullTerminated(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cDestinationNullTerminated */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_DESTINATIONNULLTERMINATED_H_ */
