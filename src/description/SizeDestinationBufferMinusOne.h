#ifndef TOOBAD4ML_DESCRIPTION_SIZEDSTMINUSONEBUFFER_H_
#define TOOBAD4ML_DESCRIPTION_SIZEDSTMINUSONEBUFFER_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cSizeDestinationBufferMinusOne: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSizeDestinationBufferMinusOne(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
