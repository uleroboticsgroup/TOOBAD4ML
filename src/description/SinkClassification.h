#ifndef TOOBAD4ML_DESCRIPTION_SINKCLASSIFICATION_H
#define TOOBAD4ML_DESCRIPTION_SINKCLASSIFICATION_H


#include "description/DescriptorDecorator.h"


namespace TOOBAD4ML {

namespace description {

/*!
 *
 */
class cSinkClassification: public cDescriptorDecorator {
public:

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 */
	cSinkClassification(IDescriptor*);


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
/* cSinkClassification */

} /* description */

} /* TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_SINKCLASSIFICATION_H */
