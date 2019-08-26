#ifndef TOOBAD4ML_DESCRIPTION_INDEXTYPE_H_
#define TOOBAD4ML_DESCRIPTION_INDEXTYPE_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {
	
/*!
 * \class cIndexType
 *
 * \brief
 * It classifies the type of the index using to access an array
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It classifies the type of index which is being used to access an array being:
 * - Constant: (p[8]) -> 0
 * - Addition (p[i+8], p[i-8]) -> 1
 * - Multiplication (p[i*8], p[i/8]) -> 2
 * - Nonlinear:  (p[i%8]) -> 3
 * - Function Call (p[foo(8)]) -> 4
 * - Array access: (p[q[i]]) -> 5
 *
 */
class cIndexType: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cIndexType(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
