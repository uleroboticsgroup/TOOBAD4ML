#ifndef TOOBAD4ML_DESCRIPTION_INPUTVALIDATIONCLASSIFICATION_H
#define TOOBAD4ML_DESCRIPTION_INPUTVALIDATIONCLASSIFICATION_H


#include "description/DescriptorDecorator.h"


namespace TOOBAD4ML {

namespace description {

/*!
 *
 */
class cInputValidationClassification: public cDescriptorDecorator {
public:

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------

    /*!
     *
     * @param
     */
	cInputValidationClassification(IDescriptor*);


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
/* cInputValidationClassification */

} /* description */

} /* TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_INPUTVALIDATIONCLASSIFICATION_H */
