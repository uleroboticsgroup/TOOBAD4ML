#ifndef TOOBAD4ML_DESCRIPTION_NUMBEROFELEMENTSCOPIEDWITHINBOUNDS_H_
#define TOOBAD4ML_DESCRIPTION_NUMBEROFELEMENTSCOPIEDWITHINBOUNDS_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cNumberOfElementsCopiedWithinBounds: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 */
	cNumberOfElementsCopiedWithinBounds(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);



}; /*cNumberOfElementsCopiedWithinBounds*/

} /* description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_NUMBEROFELEMENTSCOPIEDWITHINBOUNDS_H_ */
