#ifndef TOOBAD4ML_DESCRIPTION_LIMITCOMPLEXITY_H_
#define TOOBAD4ML_DESCRIPTION_LIMITCOMPLEXITY_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cLimitComplexity
 *
 * \brief
 * F22. Indicates the complexity of the operation performed to get the index in the
destination buffer.
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * Indicates the complexity of the operation performed to get the index used to access the data in the destination buffer. 
 * Only applicable for sink statements where the destination buffer is accessed using an index.
 * constant:              0 
 * variable:              1
 * linear expression:     2
 * non-linear expression: 3
 * function return:       4
 * array contents:        5
 *
 */
class cLimitComplexity: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cLimitComplexity(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cLimitComplexity */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_LIMITCOMPLEXITY_H_ */