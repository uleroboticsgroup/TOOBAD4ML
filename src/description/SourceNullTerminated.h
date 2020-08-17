#ifndef TOOBAD4ML_DESCRIPTION_SOURCENULLTERMINATED_H_
#define TOOBAD4ML_DESCRIPTION_SOURCENULLTERMINATED_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cSourceNullTerminated
 *
 * \brief
 * F55. Whether the source buffer is null terminated at least once in the program
 *
 * \details
 *  This class inherits from <CODE>TOOBAD4ML::description::cDescriptorDecorator</CODE>
 *  and it's an implementation of the Decorator pattern.
 * 
 *  Whether the source buffer is null terminated at least once in the program
 * 
 *  0: False
 *  1: True 
 *
 */
class cSourceNullTerminated: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cSourceNullTerminated(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cSourceNullTerminated */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_SOURCENULLTERMINATED_H_ */
