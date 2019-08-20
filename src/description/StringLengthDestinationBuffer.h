#ifndef TOOBAD4ML_DESCRIPTION_STRINGLENGTHDSTBUFFER_H_
#define TOOBAD4ML_DESCRIPTION_STRINGLENGTHDSTBUFFER_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cStringLengthDestinationBuffer: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cStringLengthDestinationBuffer(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
