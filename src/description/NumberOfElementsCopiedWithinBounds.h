#ifndef TOOBAD4ML_DESCRIPTION_NUMBEROFELEMENTSCOPIEDWITHINBOUNDS_H_
#define TOOBAD4ML_DESCRIPTION_NUMBEROFELEMENTSCOPIEDWITHINBOUNDS_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {


/*!
 * \class cNumberOfElementsCopiedWithinBounds
 *
 * \brief
 * This attribute is applicable for sinks like strncpy,
 * where the number of elements to be copied from source is specified
 * in the sink and is constant.
 *
 * \details
 * It can have one of the four values:
 * (=1) It is true if the specified number
 * of elements to be copied is not greater
 * than the destination buffer size
 * (=0) is false otherwise,
 * (=2) unknown  when it cannot be evaluated
 * (=-1) not applicable  for sinks where it does not
 * apply or when their size in not known.
 *
 */
class cNumberOfElementsCopiedWithinBounds: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cNumberOfElementsCopiedWithinBounds(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


	int StringLiteralParser(std::string);



}; /*cNumberOfElementsCopiedWithinBounds*/

} /* description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_NUMBEROFELEMENTSCOPIEDWITHINBOUNDS_H_ */
