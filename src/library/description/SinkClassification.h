#ifndef TOOBAD4ML_DESCRIPTION_SINKCLASSIFICATION_H
#define TOOBAD4ML_DESCRIPTION_SINKCLASSIFICATION_H


#include "description/DescriptorDecorator.h"


namespace TOOBAD4ML {

namespace description {

/*!
 * \class cSinkClassification
 *
 * \brief
 * Classifies the buffer overflow sinks into one of 7 types
 *
 * \details
 * A sink k is a potential vulnerable program statement
 * such that the execution of k may lead to unsafe or incorrect
 * operation if values of variables referenced at k are not
 * constrained properly. Classifies the buffer overflow sinks
 * into one of the following 7 types:
 *
 *  1. String Copy (e.g., strcpy, strncpy)
 *	2. String Concatenation (e.g., strcat, strncat)
 *	3. Memory alteration (e.g., memcpy, memmove)
 *	4. Formatted string output (e.g., sprintf, snprintf)
 *	5. Unformatted string input (e.g., gets, fgets)
 *	6. Formatted string input (e.g., scanf, sscanf)
 *	7. Array element writes: Any writes to an element of an array
 *
 */
class cSinkClassification: public cDescriptorDecorator {
public:

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------

	cSinkClassification(IDescriptor*);


    // INHERITED METHODS
    // ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};
/* cSinkClassification */

} /* description */

} /* TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_SINKCLASSIFICATION_H */
