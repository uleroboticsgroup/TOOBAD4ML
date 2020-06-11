#ifndef TOOBAD4ML_DESCRIPTION_MEMORYACCESS_H_
#define TOOBAD4ML_DESCRIPTION_MEMORYACCESS_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cMemoryAccess
 *
 * \brief
 * F3. Type of memory access performed in the potential vulnerable statement
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * It checks whether a write (array write) or a read (strcpy, scanf, etc.) was performed in the vulnerable statement.
 * 
 * 0 - None
 * 1 - Read
 * 2 - Write
 * 3 - Both
 *
 */
class cMemoryAccess: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cMemoryAccess(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cPointerDeference */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_MEMORYACCESS_H_ */
