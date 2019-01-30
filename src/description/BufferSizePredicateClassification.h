#ifndef SRC_MODELLING_BUFFERSIZEPREDICATECLASSIFICATION_H_
#define SRC_MODELLING_BUFFERSIZEPREDICATECLASSIFICATION_H_

#include "description/BufferOverflow.h"
#include "description/FeatureExtractorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cBufferSizePredicateClassification: public cFeatureExtractorDecorator {
public:

	/*!
	 *
	 * @param decoratedComponent
	 */
	cBufferSizePredicateClassification(
			IFeatureExtractor*);

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	llvm::StringRef ExtractFeature(cCodePseudoPropertyGraph&,
			cBufferOverflow&);

};
/* cBufferSizePredicateClassification */

} /* namespace description */

} /* namespace TOOBAD4ML */

#endif /* SRC_MODELLING_BUFFERSIZEPREDICATECLASSIFICATION_H_ */
