#ifndef TOOBAD4ML_DESCRIPTION_EOFCHECK_H_
#define TOOBAD4ML_DESCRIPTION_EOFCHECK_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {

/*!
 * \class cEOFCheck
 *
 * \brief
 * It checks if a EOF check is being performed over the source buffer 
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It counts how many times we can find a conditional statement where a comparison 
 * between EOF and the source buffer is performed.
 *
 */
class cEOFCheck: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cEOFCheck(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
