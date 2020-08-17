#ifndef TOOBAD4ML_DESCRIPTION_SOURCEDEPENDENTLOOPTERMINATION_H_
#define TOOBAD4ML_DESCRIPTION_SOURCEDEPENDENTLOOPTERMINATION_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cSourceDependentLoopTermination
 *
 * \brief
 * F61. Whether the sink statement is in a loop and loop termination directly or transitively refers to sink source
 *
 * \details
 *  This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 *  and it's an implementation of the Decorator pattern.
 * 
 * Whether the sink statement is in a loop and loop termination directly or transitively refers to sink source
 * 
 * -1: Not applicable
 *  0: False
 *  1: True 
 *
 */
class cSourceDependentLoopTermination: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSourceDependentLoopTermination(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cSourceDependentLoopTermination */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_SOURCEDEPENDENTLOOPTERMINATION_H_ */
