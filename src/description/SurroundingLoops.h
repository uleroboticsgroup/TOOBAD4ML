#ifndef TOOBAD4ML_DESCRIPTION_SURROUNDINGLOOPS_H_
#define TOOBAD4ML_DESCRIPTION_SURROUNDINGLOOPS_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cSurroundingLoops
 *
 * \brief
 * F8 Classification of the loop construct within which the sink statement is
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * Describes the type of loop construct within which the overflow occurs 
 *  
 * - none: 0
 * - while: 1 
 * - for: 2 
 * - nested: 3
 * 
 */
class cSurroundingLoops: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSurroundingLoops(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cSurroundingLoops */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_SURROUNDINGLOOPS_H_ */
