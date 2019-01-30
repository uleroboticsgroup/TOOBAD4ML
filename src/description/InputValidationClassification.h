#ifndef SRC_MODELLING_INPUTVALIDATIONCLASSIFICATION_H_
#define SRC_MODELLING_INPUTVALIDATIONCLASSIFICATION_H_

#include "description/CodePseudoPropertyGraph.h"
#include "description/BufferOverflow.h"
#include "description/FeatureExtractorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cInputValidationClassification: public cFeatureExtractorDecorator {
public:


	cInputValidationClassification(IFeatureExtractor*);

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	llvm::StringRef ExtractFeature(cCodePseudoPropertyGraph&,
			cBufferOverflow&);
};
/* cInputValidationClassification */

} /* namespace description */

} /* namespace TOOBAD4ML */

#endif /* SRC_MODELLING_INPUTVALIDATIONCLASSIFICATION_H_ */
