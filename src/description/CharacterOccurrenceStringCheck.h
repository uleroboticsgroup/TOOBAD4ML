//---------------------------------------------
#ifndef TOOBAD4ML_DESCRIPTION_CHAROCCURRENCESTRINGCHECK_H_
#define TOOBAD4ML_DESCRIPTION_CHAROCCURRENCESTRINGCHECK_H_
//---------------------------------------------
#include "description/DescriptorDecorator.h"

//---------------------------------------------
namespace TOOBAD4ML {
namespace description {
//---------------------------------------------

class cCharacterOccurrenceStringCheck: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cCharacterOccurrenceStringCheck(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
