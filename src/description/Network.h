#ifndef TOOBAD4ML_DESCRIPTION_NETWORK_H_
#define TOOBAD4ML_DESCRIPTION_NETWORK_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cNetwork: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 */
	cNetwork(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};
/* cInputClassification */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_NETWORK_H_ */
