#ifndef TOOBAD4ML_DESCRIPTION_SIZEDSTMINUSONEBUFFER_H_
#define TOOBAD4ML_DESCRIPTION_SIZEDSTMINUSONEBUFFER_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {

/*!
 * \class cSizeDestinationBufferMinusOne
 *
 * \brief
 * It checks if a sizeof() - 1 is being performed over the destination buffer.
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It counts how many times we can find a conditional statement where sizeof minus one is being
 * applied over the destination buffer
 *
 */
class cSizeDestinationBufferMinusOne: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSizeDestinationBufferMinusOne(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
