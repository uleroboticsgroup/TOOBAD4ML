#ifndef TOOBAD4ML_DESCRIPTION_FILE_H_
#define TOOBAD4ML_DESCRIPTION_FILE_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cFile
 *
 * \brief
 * Input Classification. Classifies the inputs as File type
 *
 * \details
 * Count the number of nodes File (e.g., fscanf, fgetc) based
 * on nature input source. Uses sink's control as well as data dependencies
 * for identifying sink input sources.  It is imperative to classify sink input
 * sources because certain type of input validation is only relevant for
 * particular input types (for example EOF check for data read from files).
 *
 */
class cFile: public cDescriptorDecorator  {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cFile(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);


}; /* cFile */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_FILE_H_ */
