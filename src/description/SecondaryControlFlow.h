#ifndef TOOBAD4ML_DESCRIPTION_SECONDARYCONTROLFLOW_H_
#define TOOBAD4ML_DESCRIPTION_SECONDARYCONTROLFLOW_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cSecondaryControlFlow
 *
 * \brief
 * F7 Classification of control flow construct that most immediately surrounds or affects the construct in Control flow type
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * Has the same values as <CODE>TOOBAD4ML::description::cControlFlow</CODE>, the difference being the location of the control flow construct
 * 
 * - none:              0 
 * - if:                1
 * - switch:            2 
 * - cond:              3
 * - goto/label:        4
 * - setjmp/longjmp:    5
 * - function pointer:  6
 * - recursion:         7
 * 
 */
class cSecondaryControlFlow: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSecondaryControlFlow(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cSecondaryControlFlow */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_SECONDARYCONTROLFLOW_H_ */
