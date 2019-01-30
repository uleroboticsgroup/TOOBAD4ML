#ifndef SRC_MODELLING_FEATUREEXTRACTORDECORATOR_H_
#define SRC_MODELLING_FEATUREEXTRACTORDECORATOR_H_

#include "description/FeatureExtractor.h"

namespace TOOBAD4ML {

namespace description {

class cFeatureExtractorDecorator: public IFeatureExtractor {

public:

	const std::string FEATURE_SEPARATOR = ";";

	/*!
	 *
	 * @param
	 */
	cFeatureExtractorDecorator(IFeatureExtractor*);


	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	virtual  llvm::StringRef ExtractFeature(cCodePseudoPropertyGraph&,
			cBufferOverflow&);

protected:

	//!
	IFeatureExtractor* m_DecoratedComponent;

};
/* cFeatureExtractorDecorator */

} /* namespace description */

} /* namespace TOOBAD4ML */

#endif /* SRC_MODELLING_FEATUREEXTRACTORDECORATOR_H_ */
