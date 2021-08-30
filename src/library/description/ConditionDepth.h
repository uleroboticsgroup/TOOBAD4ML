#ifndef TOOBAD4ML_DESCRIPTION_CONDITIONDEPTH_H_
#define TOOBAD4ML_DESCRIPTION_CONDITIONDEPTH_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cConditionDepth
 *
 * \brief
 * F11. Maximum hierarchy of condition statements that wrap the sink statement.
 *
 * \details
 *  This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 *  and it's an implementation of the Decorator pattern.
 * 
 *  Describes the maximum hierarchy of the condition statement that wraps the sink statement
 *
 */
class cConditionDepth: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cConditionDepth(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cConditionDepth */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_CONDITIONDEPTH_H_ */
