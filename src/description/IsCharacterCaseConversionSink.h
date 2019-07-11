
#ifndef SRC_DESCRIPTION_ISCHARACTERCASECONVERSIONSINK_H_
#define SRC_DESCRIPTION_ISCHARACTERCASECONVERSIONSINK_H_


#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cIsCharacterCaseConversionSink
 *
 * \brief
 * Is a character case conversion sink.
 *
 * \details
 * Operated on filled buffers. This characteristic helps in flagging that
 * no filling operation is being performed. (e.g., toupper(), tolower()).
 * This attribute is only applicable to array element write sinks.
 * Can have one of the three values:
 * (=1) True,
 * (=0) False,
 * (=-1) Not applicable, for non-array element write sinks
 *
 */
class cIsCharacterCaseConversionSink: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cIsCharacterCaseConversionSink(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

}; /*cArrayWriteIndexWithinBounds*/

} /* description */

} /* namespace TOOBAD4ML */


#endif /* SRC_DESCRIPTION_ISCHARACTERCASECONVERSIONSINK_H_ */
