#ifndef TOOBAD4ML_DESCRIPTION_POINTERDEFERENCE_H_
#define TOOBAD4ML_DESCRIPTION_POINTERDEFERENCE_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cPointerDeference
 *
 * \brief
 * F2. Indicates whether the sink statement uses a pointer dereference
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * It checks whether a pointer deference is used in the sink 
 *
 */
class cPointerDeference: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cPointerDeference(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cPointerDeference */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_POINTERDEFERENCE_H_ */
