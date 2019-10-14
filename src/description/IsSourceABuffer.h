#ifndef TOOBAD4ML_DESCRIPTION_ISSOURCEABUFFER_H_
#define TOOBAD4ML_DESCRIPTION_ISSOURCEABUFFER_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {
	
/*!
 * \class cIsSourceABuffer
 *
 * \brief
 * It classifies if the source is a buffer or not
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It classifies the type of source according to:
 * - Buffer -> 1
 * - Other -> 0
 *
 */
class cIsSourceABuffer: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cIsSourceABuffer(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
