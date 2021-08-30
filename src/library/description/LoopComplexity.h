#ifndef TOOBAD4ML_DESCRIPTION_LOOPCOMPLEXITY_H_
#define TOOBAD4ML_DESCRIPTION_LOOPCOMPLEXITY_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cLoopComplexity
 *
 * \brief
 * F9. Indicates how many loop components are more complex than the standard (initialization, test, increment)
 *
 * \details
 *  This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 *  and it's an implementation of the Decorator pattern.
 * 
 * Indicates how many loop components (initialization, test, increment) 
 * are more complex than the standard baseline of initializing to a constant, 
 * testing against a constant, and incrementing or decrementing by one
 * 
 * - n/a:  -1
 * - none:  0
 * - one:   1
 * - two:   2
 * - three: 3
 *
 */
class cLoopComplexity: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cLoopComplexity(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cLoopComplexity */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_LOOPCOMPLEXITY_H_ */
