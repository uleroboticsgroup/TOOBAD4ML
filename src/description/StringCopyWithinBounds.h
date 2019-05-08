
#ifndef SRC_DESCRIPTION_STRINGCOPYWITHINBOUNDS_H_
#define SRC_DESCRIPTION_STRINGCOPYWITHINBOUNDS_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cStringCopyWithinBounds: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 */
	cStringCopyWithinBounds(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /*cFormatStringPrecisionWithinBounds*/

} /* description */

} /* namespace TOOBAD4ML */


#endif /* SRC_DESCRIPTION_STRINGCOPYWITHINBOUNDS_H_ */
