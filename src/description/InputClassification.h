#ifndef SRC_MODELLING_INPUTCLASSIFICATION_H_
#define SRC_MODELLING_INPUTCLASSIFICATION_H_

#include "description/CodePseudoPropertyGraph.h"
#include "description/BufferOverflow.h"
#include "description/FeatureExtractorDecorator.h"


namespace TOOBAD4ML {

namespace description {

class cInputClassification: public cFeatureExtractorDecorator {
public:

	/*!
	 *
	 * @param
	 */
	cInputClassification(IFeatureExtractor*);

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	llvm::StringRef ExtractFeature(cCodePseudoPropertyGraph&,
			cBufferOverflow&);
};
/* cInputClassification */

} /* namespace description */

} /* namespace TOOBAD4ML */

#endif /* SRC_MODELLING_INPUTCLASSIFICATION_H_ */
