// ------------------------------------------------------------------------
#ifndef TOOBAD4ML_DESCRIPTION_CHARCHECK_H_
#define TOOBAD4ML_DESCRIPTION_CHARCHECK_H_
// ------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace description {
// ------------------------------------------------------------------------
/*!
 * \class cCharacterCheck
 *
 * \brief
 * It checks if the source buffer is a char or int and if it's performing 
 * a check. 
 *
 * \details
 * This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 * and it's an implementation of the Decorator pattern.
 * It counts how many times we can find a conditional statement where the source 
 * buffer is invoved, being it a char or an int.
 *
 */
class cCharacterCheck: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------
	cCharacterCheck(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------
	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
