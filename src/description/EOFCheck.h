#ifndef TOOBAD4ML_DESCRIPTION_EOFCHECK_H_
#define TOOBAD4ML_DESCRIPTION_EOFCHECK_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

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
