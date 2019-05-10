
#ifndef SRC_DESCRIPTION_ISCHARACTERCASECONVERSIONSINK_H_
#define SRC_DESCRIPTION_ISCHARACTERCASECONVERSIONSINK_H_


#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cIsCharacterCaseConversionSink: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 */
	cIsCharacterCaseConversionSink(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

}; /*cArrayWriteIndexWithinBounds*/


} /* description */


} /* namespace TOOBAD4ML */


#endif /* SRC_DESCRIPTION_ISCHARACTERCASECONVERSIONSINK_H_ */
