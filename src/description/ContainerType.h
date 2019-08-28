#ifndef TOOBAD4ML_DESCRIPTION_CONTAINERTYPE_H_
#define TOOBAD4ML_DESCRIPTION_CONTAINERTYPE_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {
	
/*!
 * \class cContainerType
 *
 * \brief
 * It classifies the type of container that holds the buffer
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It classifies the type of container that has the destination buffer:
 * - None: (p[256]) -> 0
 * - Array: (p[256][2]) -> 1
 * - Struct/Union (struct.p[256], union.p[256]) -> 2
 * - Others: (?) -> 3
 */
class cContainerType: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cContainerType(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
