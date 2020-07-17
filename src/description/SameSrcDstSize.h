#ifndef TOOBAD4ML_DESCRIPTION_SAMESRCDSTSIZE_H_
#define TOOBAD4ML_DESCRIPTION_SAMESRCDSTSIZE_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cSameSrcDstSize
 *
 * \brief
 * F59. Whether the source and destination buffers have the same size
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * 
 * Whether the source and destination buffers have the same size.
 * 
 * -1: Not applicable
 *  0: False (they don't have the same size)
 *  1: True (they do)
 *
 */
class cSameSrcDstSize: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSameSrcDstSize(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cSameSrcDstSize */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_SAMESRCDSTSIZE_H_ */
