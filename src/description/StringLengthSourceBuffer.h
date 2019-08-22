#ifndef TOOBAD4ML_DESCRIPTION_STRINGLENGTHSOURCEBUFFER_H_
#define TOOBAD4ML_DESCRIPTION_STRINGLENGTHSOURCEBUFFER_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {

/*!
 * \class cStringLengthSourceBuffer
 *
 * \brief
 * It checks if the source buffer is used inside <CODE>strlen()</CODE> 
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It counts how many times we can find a conditional statement where the source
 * buffer is used inside <CODE>strlen()</CODE>.
 *
 */
class cStringLengthSourceBuffer: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cStringLengthSourceBuffer(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
