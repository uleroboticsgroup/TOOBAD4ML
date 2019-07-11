
#ifndef SRC_DESCRIPTION_STRINGCOPYWITHINBOUNDS_H_
#define SRC_DESCRIPTION_STRINGCOPYWITHINBOUNDS_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cStringCopyWithinBounds
 *
 * \brief
 * Checks if the size of elements to be copied
 * is not greater than the destination buffer size.
 *
 * \details
 * This is applicable for strcpy sinks with a string literal
 * as source string and with known destination buffer size.
 * It can have one of the three values:
 * (=1) True, when string length of string literal
 * is less than destination buffer size,
 * (=0) False, if vice-versa.
 * (=-1) Not applicable, when the source is not a string
 * literal or sink is not strcpy call.
 *
 *
 */
class cStringCopyWithinBounds: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cStringCopyWithinBounds(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /*cFormatStringPrecisionWithinBounds*/

} /* description */

} /* namespace TOOBAD4ML */


#endif /* SRC_DESCRIPTION_STRINGCOPYWITHINBOUNDS_H_ */
