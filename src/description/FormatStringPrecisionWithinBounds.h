#ifndef TOOBAD4ML_DESCRIPTION_FORMATSTRINGPRECISIONWITHINBOUNDS_H_
#define TOOBAD4ML_DESCRIPTION_FORMATSTRINGPRECISIONWITHINBOUNDS_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cFormatStringPrecisionWithinBounds: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 */
	cFormatStringPrecisionWithinBounds(IDescriptor*);


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

#endif /* SRC_DESCRIPTION_FORMATSTRINGPRECISIONWITHINBOUNDS_H_ */
