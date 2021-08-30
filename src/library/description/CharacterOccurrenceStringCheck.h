// ------------------------------------------------------------------------
#ifndef TOOBAD4ML_DESCRIPTION_CHAROCCURRENCESTRINGCHECK_H_
#define TOOBAD4ML_DESCRIPTION_CHAROCCURRENCESTRINGCHECK_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"

// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {
// ------------------------------------------------------------------------
/*!
 * \class cCharacterOccurrenceStringCheck
 *
 * \brief
 * It checks if the source buffer is used in strchr, strpbrk, memchr 
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It counts how many times we can find a conditional statement where the source 
 * buffer is used in one of the following functions: 
 * 	- strchr
 * 	- strpbrk
 * 	- memchr 
 *
 */
class cCharacterOccurrenceStringCheck: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cCharacterOccurrenceStringCheck(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
