#ifndef TOOBAD4ML_DESCRIPTION_INPUTCLASSIFICATION_H
#define TOOBAD4ML_DESCRIPTION_INPUTCLASSIFICATION_H


#include "description/DescriptorDecorator.h"


namespace TOOBAD4ML {

namespace description {

/*!
 *
 */
class cInputClassification: public cDescriptorDecorator {
public:

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 */
	cInputClassification(IDescriptor*);


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
/* cInputClassification */

} /* description */

} /* TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_INPUTCLASSIFICATION_H */
