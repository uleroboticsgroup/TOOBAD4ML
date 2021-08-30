#ifndef TOOBAD4ML_DESCRIPTION_INPUTCOUNT_H_
#define TOOBAD4ML_DESCRIPTION_INPUTCOUNT_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cInputCount
 *
 * \brief
 * F51. Counts the number of sink inputs
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * Counts the number of sink inputs, i.e. number of instructions that perform a write
 * operation over the source buffer
 *
 */
class cInputCount: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cInputCount(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cInputCount */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_INPUTCOUNT_H_ */
