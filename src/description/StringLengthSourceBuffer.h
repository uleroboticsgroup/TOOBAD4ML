#ifndef TOOBAD4ML_DESCRIPTION_STRINGLENGTHSOURCEBUFFER_H_
#define TOOBAD4ML_DESCRIPTION_STRINGLENGTHSOURCEBUFFER_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cStringLengthSourceBuffer: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cStringLengthSourceBuffer(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
