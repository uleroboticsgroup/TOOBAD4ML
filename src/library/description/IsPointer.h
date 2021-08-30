#ifndef TOOBAD4ML_DESCRIPTION_ISPOINTER_H_
#define TOOBAD4ML_DESCRIPTION_ISPOINTER_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {
	
/*!
 * \class cIsPointer
 *
 * \brief
 * It classifies if the destination is a pointer or not
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It classifies the type of destination according to:
 * - Pointer -> 1
 * - Other -> 0
 *
 */
class cIsPointer: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cIsPointer(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
