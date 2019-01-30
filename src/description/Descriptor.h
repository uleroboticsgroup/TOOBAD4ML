#ifndef SRC_MODELLING_DESCRIPTOR_H_
#define SRC_MODELLING_DESCRIPTOR_H_

#include "description/FeatureExtractor.h"

namespace TOOBAD4ML {

namespace description {

class cDescriptor: public IFeatureExtractor {

public:

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	llvm::StringRef ExtractFeature(cCodePseudoPropertyGraph&,
			cBufferOverflow&);

};
/* cDescriptor */

} /* namespace description */

} /* namespace TOOBAD4ML */

#endif /* SRC_MODELLING_FEATUREEXTRACTORDECORATOR_H_ */
