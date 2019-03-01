// ----------------------------------------------------------------------------
#ifndef TOOBAD4ML_DESCRIPTION_MOCKDESCRIPTOR_H
#define TOOBAD4ML_DESCRIPTION_MOCKDESCRIPTOR_H
// ----------------------------------------------------------------------------
#include "description/Descriptor.h"
// ----------------------------------------------------------------------------


namespace TOOBAD4ML {

namespace description {

/*!
 * \class cMockDescriptor
 *
 * \brief
 * A mock descriptor used as a base for building compound descriptors (model).
 *
 * \details
 * This is a base class for the Decorator design pattern. It is just a mock
 * class intended to serve as a base for adding instances of
 * {\ref cDescriptorDecorator}, as expected with the Decorator design pattern.
 * The resulting descriptor makes a model that describes Buffer Overflow
 * features.
 */
class cMockDescriptor: public IDescriptor {

    // IDESCRIPTOR INHERITED METHODS
    // ------------------------------------------------------------------------

public:

	/*!
     * MOCK METHOD! Expects to extract a Buffer Overflow feature from a Code
     * Property Graph.
     *
	 * @return An empty string.
	 */
	llvm::StringRef ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

}; /* cMockDescriptor */

} // namespace description

} // namespace TOOBAD4ML

#endif
