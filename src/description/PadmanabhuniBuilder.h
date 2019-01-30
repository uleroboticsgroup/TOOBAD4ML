#ifndef SRC_MODELLING_PADMANABHUNIBUILDER_H_
#define SRC_MODELLING_PADMANABHUNIBUILDER_H_

#include "description/DescriptorBuilder.h"

namespace TOOBAD4ML {

namespace description {

class cPadmanabhuniBuilder: public IDescriptorBuilder {
public:
	/*!
	 *
	 * @return
	 */
	IFeatureExtractor* CreateDescriptor();

};
/* cPadmanabhuniBuilder */

} /* namespace description */

} /* namespace TOOBAD4ML */

#endif /* SRC_MODELLING_PADMANABHUNIBUILDER_H_ */
