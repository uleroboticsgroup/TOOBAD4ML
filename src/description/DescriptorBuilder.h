#ifndef SRC_MODELLING_DESCRIPTORBUILDER_H_
#define SRC_MODELLING_DESCRIPTORBUILDER_H_

#include "description/FeatureExtractor.h"

namespace TOOBAD4ML {

namespace description {

class IDescriptorBuilder {
public:

	/*!
	 *
	 * @return
	 */
	virtual IFeatureExtractor* CreateDescriptor() = 0;



};
/* IDescriptorBuilder */

} /* namespace description */

} /* namespace TOOBAD4ML */

#endif /* SRC_MODELLING_DESCRIPTORBUILDER_H_ */
