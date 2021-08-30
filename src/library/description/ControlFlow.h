#ifndef TOOBAD4ML_DESCRIPTION_CONTROLFLOW_H_
#define TOOBAD4ML_DESCRIPTION_CONTROLFLOW_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cControlFlow
 *
 * \brief
 * F6 Classification of control flow construct that most immediately surrounds or affects the sink statement
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * Describes what kind of program control flow most immediately surrounds or affects the overflow
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
class cControlFlow: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cControlFlow(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cControlFlow */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_CONTROLFLOW_H_ */
