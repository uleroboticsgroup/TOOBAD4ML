#ifndef TOOBAD4ML_DESCRIPTION_NULLCHECK_H_
#define TOOBAD4ML_DESCRIPTION_NULLCHECK_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {
	
/*!
 * \class cNULLCheck
 *
 * \brief
 * It checks if a NULL check is being performed over the source buffer 
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It counts how many times we can find a conditional statement where a comparison 
 * between NULL and the source buffer is performed.
 *
 */
class cNULLCheck: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cNULLCheck(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
