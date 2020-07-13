#ifndef TOOBAD4ML_DESCRIPTION_DATASIZE_H_
#define TOOBAD4ML_DESCRIPTION_DATASIZE_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cDataSize
 *
 * \brief
 * F27. How much data is read or written beyond the boundary
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * How much data is read or written beyond the boundar in bytes
 *
 */
class cDataSize: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cDataSize(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cDataSize */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_DATASIZE_H_ */
