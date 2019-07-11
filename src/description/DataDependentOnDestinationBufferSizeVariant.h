
#ifndef SRC_DESCRIPTION_DATADEPENDENTONDESTINATIONBUFFERSIZEVARIANT_H_
#define SRC_DESCRIPTION_DATADEPENDENTONDESTINATIONBUFFERSIZEVARIANT_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cDataDependentOnDestinationBufferSizeVariant: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 */
	cDataDependentOnDestinationBufferSizeVariant(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

}; /*cArrayWriteIndexWithinBounds*/

} /* description */


} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_DATADEPENDENTONDESTINATIONBUFFERSIZE_H_ */
