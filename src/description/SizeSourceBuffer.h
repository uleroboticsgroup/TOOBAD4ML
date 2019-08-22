#ifndef TOOBAD4ML_DESCRIPTION_SIZESOURCEBUFFER_H_
#define TOOBAD4ML_DESCRIPTION_SIZESOURCEBUFFER_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {

/*!
 * \class cSizeSourceBuffer
 *
 * \brief
 * It checks if a sizeof() is being performed over the source buffer.
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It counts how many times we can find a conditional statement where sizeof is being
 * applied over the source buffer
 *
 */
class cSizeSourceBuffer: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSizeSourceBuffer(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
