#ifndef TOOBAD4ML_DESCRIPTION_DATABUFFERDECLARATION_H_
#define TOOBAD4ML_DESCRIPTION_DATABUFFERDECLARATION_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cDataBufferDeclaration: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 */
	cDataBufferDeclaration(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};/* cDataBufferDeclration */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_DATABUFFERDECLRATION_H_ */
