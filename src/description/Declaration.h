#ifndef TOOBAD4ML_DESCRIPTION_DECLARATION_H_
#define TOOBAD4ML_DESCRIPTION_DECLARATION_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cDeclaration
 *
 * \brief
 * F60. Type of declaration of the destination buffer
 *
 * \details
 *  This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 *  and it's an implementation of the Decorator pattern.
 * 
 *  Whether the source and destination buffers have the same size.
 * 
 * -1: Not applicable
 *  0: static
 *  1: dynamic source dependent
 *  2: dynamic source independent
 *  3: dynamic constant
 *  4: mixed
 *
 */
class cDeclaration: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cDeclaration(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cDeclaration */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_SAMESRCDSTSIZE_H_ */
