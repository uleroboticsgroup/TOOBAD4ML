#ifndef SRC_MODELLING_SINKCLASSIFICATION_H_
#define SRC_MODELLING_SINKCLASSIFICATION_H_

#include "description/CodePseudoPropertyGraph.h"
#include "description/BufferOverflow.h"
#include "description/FeatureExtractorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cSinkClassification: public cFeatureExtractorDecorator {
public:

	/*!
	 *
	 * @param
	 */
	cSinkClassification(IFeatureExtractor*);

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	llvm::StringRef ExtractFeature(cCodePseudoPropertyGraph&,
			cBufferOverflow&);

};
/* cSinkClassification */

} /* namespace description */

} /* namespace TOOBAD4ML */

#endif /* SRC_MODELLING_SINKCLASSIFICATION_H_ */
