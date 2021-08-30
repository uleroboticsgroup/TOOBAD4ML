#ifndef TOOBAD4ML_DESCRIPTION_CONTAINER_H_
#define TOOBAD4ML_DESCRIPTION_CONTAINER_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cContainer
 *
 * \brief
 * F12. Structure in which the destination buffer is wrapped
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * Structure in which the destination buffer is wrapped
 * 
 * 0 - None
 * 1 - Array 
 * 2 - Struct
 * 3 - Union
 * 4 - Array of structs
 * 5 - Array of unions
 *
 */
class cContainer: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cContainer(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cPointerDeference */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_CONTAINER_H_ */
