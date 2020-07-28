#ifndef TOOBAD4ML_DESCRIPTION_VALIDATION_H_
#define TOOBAD4ML_DESCRIPTION_VALIDATION_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cValidation
 *
 * \brief
 * F62. Counts the number of sink validation nodes
 *
 * \details
 *  This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 *  and it's an implementation of the Decorator pattern.
 * 
 *  Counts the number of sink validation nodes
 *
 */
class cValidation: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cValidation(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cValidation */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_VALIDATION_H_ */
