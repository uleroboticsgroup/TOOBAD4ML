#ifndef TOOBAD4ML_DESCRIPTION_DATATYPE_H_
#define TOOBAD4ML_DESCRIPTION_DATATYPE_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cDataType
 *
 * \brief
 * F14. Indicates the type of data stored in the destination buffer
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * Indicates the type of data stored in the destination buffer
 * character:          0 
 * integer:            1
 * floating point:     2
 * wide character:     3
 * pointer:            4
 * unsigned integer:   5
 *
 */
class cDataType: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cDataType(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cDataType */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_POINTERDEFERENCE_H_ */
