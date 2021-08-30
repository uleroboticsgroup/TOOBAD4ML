#ifndef TOOBAD4ML_DESCRIPTION_INDEXCOMPLEXITY_H_
#define TOOBAD4ML_DESCRIPTION_INDEXCOMPLEXITY_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cIndexComplexity
 *
 * \brief
 * F18. Indicates the complexity of the operation performed to get the index in the
destination buffer.
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * Indicates the complexity of the operation performed to get the index used t access the data in the destination buffer. 
 * Only applicable for sink statements where the destination buffer is accessed using an index.
 * constant:              0 
 * variable:              1
 * linear expression:     2
 * non-linear expression: 3
 * function return:       4
 * array contents:        5
 *
 */
class cIndexComplexity: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cIndexComplexity(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cIndexComplexity */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_INDEXCOMPLEXITY_H_ */
