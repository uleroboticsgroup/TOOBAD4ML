#ifndef TOOBAD4ML_DESCRIPTION_STRINGCOMPARISON_H_
#define TOOBAD4ML_DESCRIPTION_STRINGCOMPARISON_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {

/*!
 * \class cStringComparison
 *
 * \brief
 * It checks if the source buffer is used in strcmp, strncmp
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It counts how many times we can find a conditional statement where the source 
 * buffer is used in one of the following functions: 
 * 	- strcmp
 * 	- strncmp
 *
 */
class cStringComparison: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cStringComparison(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
