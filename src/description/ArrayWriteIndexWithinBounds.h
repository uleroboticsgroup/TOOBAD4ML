
#ifndef TOOBAD4ML_DESCRIPTION_ARRAYWRITEINDEXWITHINBOUNDS_H_
#define TOOBAD4ML_DESCRIPTION_ARRAYWRITEINDEXWITHINBOUNDS_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {


/*!
 * \class cArrayWriteIndexWithinBounds
 *
 * \brief
 * Checks if the size of elements to be copied
 * is not greater than the destination buffer size.
 *
 * \details
 * This is only applicable for array writes sinks
 * with constant index value and known buffer size.
 * It can have one of the three values:
 * (=1) True
 * (=0) False
 * (=-1) Not applicable (e.g., index value is not present)
 */
class cArrayWriteIndexWithinBounds: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cArrayWriteIndexWithinBounds(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

}; /*cArrayWriteIndexWithinBounds*/

} /* description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_ARRAYWRITEINDEXWITHINBOUNDS_H_ */
