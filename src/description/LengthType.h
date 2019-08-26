#ifndef TOOBAD4ML_DESCRIPTION_LENGTHTYPE_H_
#define TOOBAD4ML_DESCRIPTION_LENGTHTYPE_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {
	
/*!
 * \class cIndexType
 *
 * \brief
 * It classifies the type of the length in <CODE>memcpy</CODE> function
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It classifies the type of length being used in <CODE>memcpy</CODE> function
 * - Constant: (memcpy(buffer, buffer2, 256)) -> 0
 * - Addition: (memcpy(buffer, buffer2, 256+2)) -> 1
 * - Multiplication: (memcpy(buffer, buffer2, 256 * 3)) -> 2
 * - Nonlinear: (memcpy(buffer, buffer2, 256 % 3)) -> 3
 * - Function Call: (memcpy(buffer, buffer2, foo())) -> 4
 * - Array access: (memcpy(buffer, buffer2, buffer3[?])) -> 5
 *
 */
class cLengthType: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cLengthType(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
