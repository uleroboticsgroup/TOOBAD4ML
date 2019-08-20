#ifndef TOOBAD4ML_DESCRIPTION_SIZEDSTMINUSXBUFFER_H_
#define TOOBAD4ML_DESCRIPTION_SIZEDSTMINUSXBUFFER_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cSizeDestinationBufferMinusX: public cDescriptorDecorator {
public:

	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSizeDestinationBufferMinusX(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

}

}

#endif
