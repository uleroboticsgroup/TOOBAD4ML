#ifndef TOOBAD4ML_DESCRIPTION_SIZEDSTBUFFER_H_
#define TOOBAD4ML_DESCRIPTION_SIZEDSTBUFFER_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cSizeDestinationBuffer: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSizeDestinationBuffer(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
