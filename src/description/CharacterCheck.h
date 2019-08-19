//---------------------------------------------
#ifndef TOOBAD4ML_DESCRIPTION_CHARCHECK_H_
#define TOOBAD4ML_DESCRIPTION_CHARCHECK_H_
//---------------------------------------------
#include "description/DescriptorDecorator.h"

//---------------------------------------------
namespace TOOBAD4ML {
namespace description {
//---------------------------------------------

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
