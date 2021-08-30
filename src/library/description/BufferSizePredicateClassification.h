#ifndef TOOBAD4ML_DESCRIPTION_BUFFERSIZEPREDICATECLASSIFICATION_H
#define TOOBAD4ML_DESCRIPTION_BUFFERSIZEPREDICATECLASSIFICATION_H


#include "description/DescriptorDecorator.h"


namespace TOOBAD4ML {

namespace description {


/*!
 *
 */
class cBufferSizePredicateClassification: public cDescriptorDecorator {
public:

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------

	/*!
	 *
	 * @param decoratedComponent
	 */
	cBufferSizePredicateClassification(IDescriptor*);


    // INHERITED METHODS
    // ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	std::string ExtractFeature(cCodePropertyGraph&,	cBufferOverflow&);

};
/* cBufferSizePredicateClassification */

} /* description */

} /* TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_BUFFERSIZEPREDICATECLASSIFICATION_H */
