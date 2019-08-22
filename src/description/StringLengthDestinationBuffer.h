#ifndef TOOBAD4ML_DESCRIPTION_STRINGLENGTHDSTBUFFER_H_
#define TOOBAD4ML_DESCRIPTION_STRINGLENGTHDSTBUFFER_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {

namespace description {
/*!
 * \class cStringLengthDestinationBuffer
 *
 * \brief
 * It checks if the destination buffer is used inside <CODE>strlen()</CODE> 
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It counts how many times we can find a conditional statement where the destination
 * buffer is used inside <CODE>strlen()</CODE>.
 *
 */
class cStringLengthDestinationBuffer: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cStringLengthDestinationBuffer(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
