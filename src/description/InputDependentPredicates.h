#ifndef TOOBAD4ML_DESCRIPTION_INPUTDEPENDENTPREDICATES_H_
#define TOOBAD4ML_DESCRIPTION_INPUTDEPENDENTPREDICATES_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cInputDependentPredicates
 *
 * \brief
 * F63. Counts the number of sink validation nodes
 *
 * \details
 *  This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 *  and it's an implementation of the Decorator pattern.
 * 
 *  Counts the number of sink validation nodes
 *
 */
class cInputDependentPredicates: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cInputDependentPredicates(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cInputDependentPredicates */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_INPUTDEPENDENTPREDICATES_H_ */
