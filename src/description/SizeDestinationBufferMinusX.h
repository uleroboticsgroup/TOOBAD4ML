#ifndef TOOBAD4ML_DESCRIPTION_SIZEDSTMINUSXBUFFER_H_
#define TOOBAD4ML_DESCRIPTION_SIZEDSTMINUSXBUFFER_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {

/*!
 * \class cSizeDestinationBufferMinusX
 *
 * \brief
 * It checks if a sizeof() - x is being performed over the destination buffer.
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It counts how many times we can find a conditional statement where sizeof minus x 
 * (being x any value which is greater than 1) is being applied over the destination buffer
 *
 */
class cSizeDestinationBufferMinusX: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSizeDestinationBufferMinusX(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
