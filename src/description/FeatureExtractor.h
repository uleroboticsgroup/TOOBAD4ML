#ifndef SRC_MODELLING_FEATUREEXTRACTOR_H_
#define SRC_MODELLING_FEATUREEXTRACTOR_H_

#include "description/BufferOverflow.h"
#include "description/CodePseudoPropertyGraph.h"

namespace TOOBAD4ML {

namespace description {

class IFeatureExtractor {

public:

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	virtual llvm::StringRef ExtractFeature(cCodePseudoPropertyGraph&,
			cBufferOverflow&) = 0;
};
/* IFeatureExtractor */

} /* namespace description */

} /* namespace TOOBAD4ML */

#endif /* SRC_MODELLING_FEATUREEXTRACTOR_H_ */
