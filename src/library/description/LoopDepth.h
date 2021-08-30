#ifndef TOOBAD4ML_DESCRIPTION_LOOPDEPTH_H_
#define TOOBAD4ML_DESCRIPTION_LOOPDEPTH_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cLoopDepth
 *
 * \brief
 * F10. Maximum hierarchy of the loop statement that wraps the sink statement.
 *
 * \details
 *  This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 *  and it's an implementation of the Decorator pattern.
 * 
 *  Describes the maximum hierarchy of the loop statement that wraps the sink statement
 *
 */
class cLoopDepth: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cLoopDepth(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cLoopDepth */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_LOOPDEPTH_H_ */
