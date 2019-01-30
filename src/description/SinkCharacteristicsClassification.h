#ifndef SRC_MODELLING_SINKCHARACTERISTICSCLASSIFICATION_H_
#define SRC_MODELLING_SINKCHARACTERISTICSCLASSIFICATION_H_

#include "description/CodePseudoPropertyGraph.h"
#include "description/BufferOverflow.h"
#include "description/FeatureExtractorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cSinkCharacteristicsClassification : public cFeatureExtractorDecorator {
public:

	/*!
	 *
	 * @param
	 */
	cSinkCharacteristicsClassification(IFeatureExtractor*);

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	llvm::StringRef ExtractFeature(cCodePseudoPropertyGraph&,
			cBufferOverflow&);
};
/* cSinkCharacteristicsClassification */

} /* namespace description */

} /* namespace TOOBAD4ML */

#endif /* SRC_MODELLING_SINKCHARACTERISTICSCLASSIFICATION_H_ */
