#ifndef TOOBAD4ML_DESCRIPTION_NETWORK_H_
#define TOOBAD4ML_DESCRIPTION_NETWORK_H_

#include "description/DescriptorDecorator.h"

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cNetwork
 *
 * \brief
 * Input Classification. Classifies the inputs as Network type
 *
 * \details
 * Count the number of nodes Network (e.g., recv, recvfrom, recvmsg) based
 * on nature input source. Uses sink's control as well as data dependencies
 * for identifying sink input sources.  It is imperative to classify sink input
 * sources because certain type of input validation is only relevant for
 * particular input types (for example EOF check for data read from files).
 *
 */
class cNetwork: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cNetwork(IDescriptor*);

	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

};
/* cInputClassification */

} /* description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_NETWORK_H_ */
