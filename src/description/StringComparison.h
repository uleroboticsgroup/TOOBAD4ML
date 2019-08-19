#ifndef TOOBAD4ML_DESCRIPTION_STRINGCOMPARISON_H_
#define TOOBAD4ML_DESCRIPTION_STRINGCOMPARISON_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

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
