#ifndef TOOBAD4ML_DESCRIPTION_FILE_H_
#define TOOBAD4ML_DESCRIPTION_FILE_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cFile: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 */
	cFile(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);



}; /* cFile */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_FILE_H_ */
