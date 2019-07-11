
#ifndef SRC_DESCRIPTION_RESETSINCONTROLPREDICATES_H_
#define SRC_DESCRIPTION_RESETSINCONTROLPREDICATES_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

class cResetsInControlPredicates: 	public cDescriptorDecorator {
	public:
		// CONSTRUCTORS & DESTRUCTORS
		// ------------------------------------------------------------------------

		/*!
		 *
		 * @param
		 */
		cResetsInControlPredicates(IDescriptor*);


		// INHERITED METHODS
		// ------------------------------------------------------------------------

		/*!
		 *
		 * @param
		 * @param
		 * @return
		 */
		std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};

} /* namespace description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_RESETSINCONTROLPREDICATES_H_ */
