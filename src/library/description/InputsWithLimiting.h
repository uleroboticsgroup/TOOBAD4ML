#ifndef TOOBAD4ML_DESCRIPTION_INPUTSWITHLIMITING_H_
#define TOOBAD4ML_DESCRIPTION_INPUTSWITHLIMITING_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cInputsWithLimiting
 *
 * \brief
 * F52. Counts the number of sink inputs which have been received by imposing length restrictions
 *
 * \details
 *  This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 *  and it's an implementation of the Decorator pattern.
 * 
 *  Counts the number of sink inputs which have been received by imposing length restrictions
 *
 */
class cInputsWithLimiting: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cInputsWithLimiting(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cInputsWithLimiting */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_INPUTSWITHLIMITING_H_ */
