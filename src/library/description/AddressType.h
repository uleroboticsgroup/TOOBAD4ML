#ifndef TOOBAD4ML_DESCRIPTION_ADDRESSTYPE_H_
#define TOOBAD4ML_DESCRIPTION_ADDRESSTYPE_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {
	
/*!
 * \class cAddressType
 *
 * \brief
 * It classifies the type of the address using to access a pointer
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It classifies the type of address which is being used to access a pointer being:
 * - Constant: (Not applicable) -> 0
 * - Addition (*p(i+8), *p(i-8)) -> 1
 * - Multiplication (*p(i*8), *p(i/8)) -> 2
 * - Nonlinear:  (*p(i%8)) -> 3
 * - Function Call (*p(foo(8))) -> 4
 * - Array access: (*p(q(i))) -> 5
 *
 */
class cAddressType: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cAddressType(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
