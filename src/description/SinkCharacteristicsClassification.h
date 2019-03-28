#ifndef TOOBAD4ML_DESCRIPTION_SINKCHARACTERISTICSCLASSIFICATION_H
#define TOOBAD4ML_DESCRIPTION_SINKCHARACTERISTICSCLASSIFICATION_H


#include "description/DescriptorDecorator.h"


namespace TOOBAD4ML {

namespace description {


/*!
 *
 */
class cSinkCharacteristicsClassification : public cDescriptorDecorator {
public:

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 */
	cSinkCharacteristicsClassification(IDescriptor*);


    // INHERITED METHODS
    // ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);
};
/* cSinkCharacteristicsClassification */

} /* description */

} /* TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_SINKCHARACTERISTICSCLASSIFICATION_H */
