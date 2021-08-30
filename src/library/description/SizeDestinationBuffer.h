#ifndef TOOBAD4ML_DESCRIPTION_SIZEDSTBUFFER_H_
#define TOOBAD4ML_DESCRIPTION_SIZEDSTBUFFER_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {

/*!
 * \class cSizeDestinationBuffer
 *
 * \brief
 * It checks if a sizeof() is being performed over the destination buffer.
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It counts how many times we can find a conditional statement where sizeof is being
 * applied over the destination buffer
 *
 */
class cSizeDestinationBuffer: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSizeDestinationBuffer(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
