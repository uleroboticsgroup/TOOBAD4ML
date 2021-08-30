// ----------------------------------------------------------------------------
#ifndef TOOBAD4ML_DESCRIPTION_PADMANABHUNIBUILDER_H
#define TOOBAD4ML_DESCRIPTION_PADMANABHUNIBUILDER_H
// ----------------------------------------------------------------------------
#include "description/DescriptorBuilder.h"
// ----------------------------------------------------------------------------


namespace TOOBAD4ML {

namespace description {

/*!
 * \class cPadmanabhuniBuilder
 *
 * \brief
 * Creates a Padmanabhuni's model for describing Buffer Overflow
 * vulnerabilities.
 *
 * \details
 * This class creates the model proposed by (Padmanabhuni & Tan, 2014), which
 * describes a Buffer Overflow using 5 features:
 *
 *      1. Sink Classification {\see cSinkClassification}
 *      2. Input Classification {\see cInputClassification}
 *      3. Input Validation {\see cInputValidation}
 *      4. Buffer Size Predicate Classification {\see cBufferSizePredicate}
 *      5. Sink Characteristics Classification
 *         {\see cSinkCharacteristicsClassification}
 *
 *
 * REFERENCES
 * ----------------------------------------------------------------------------
 *
 * (Padmanabhuni & Tan, 2014) Padmanabhuni, B. M., & Tan, H. B. K. (2014,
 *      November). Predicting Buffer Overflow Vulnerabilities through Mining
 *      Light-Weight Static Code Attributes. In 2014 IEEE International
 *      Symposium on Software Reliability Engineering Workshops (pp 317-322).
 *      IEEE.
 */
class cPadmanabhuniBuilder: public IDescriptorBuilder {

    // IDESCRIPTORBUILDER INHERITED METHODS
    // ------------------------------------------------------------------------

public:

	/*!
	 * Creates a model to describe a Buffer Overflow vulnerability according
     * to Padmanabhuni's purpose.
     *
	 * @return A model describing a Buffer Overflow vulnerability.
	 */
	IDescriptor* CreateDescriptor();

}; /* cPadmanabhuniBuilder */

} // namespace description

} // namespace TOOBAD4ML

#endif
