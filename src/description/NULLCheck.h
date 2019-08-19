#ifndef TOOBAD4ML_DESCRIPTION_NULLCHECK_H_
#define TOOBAD4ML_DESCRIPTION_NULLCHECK_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

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
