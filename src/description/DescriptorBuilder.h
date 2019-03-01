// ----------------------------------------------------------------------------
#ifndef TOOBAD4ML_DESCRIPTION_DESCRIPTORBUILDER_H
#define TOOBAD4ML_DESCRIPTION_DESCRIPTORBUILDER_H
// ----------------------------------------------------------------------------

namespace TOOBAD4ML {

namespace description {


// CLASS FORWARDING
// ----------------------------------------------------------------------------

class IDescriptor;


// CLASS DEFINITION
// ----------------------------------------------------------------------------

/*!
 * \class IDescriptorBuilder
 *
 * \brief
 * A builder to create models that describe Buffer Overflow vulnerabilities.
 *
 * \details
 * This is just the interface for the Builder design pattern. It declares a
 * single method intended for creating instances of {\ref IDescriptor}, that
 * is, a model to describe a Buffer Overflow vulnerability. This kind of model
 * is built by adding features (child classes of {\ref cDescriptorDecorator})
 * to a base descriptor ({\ref cMockDescriptor}); as intended in the Decorator
 * design pattern.
 */
class IDescriptorBuilder {

    // INTERFACE METHODS
    // ------------------------------------------------------------------------

public:

	/*!
	 * Creates a model to describe a Buffer Overflow vulnerability by
     * decorating several features from a {\ref } into a {}.
     *
	 * @return A model describing a Buffer Overflow vulnerability.
	 */
	virtual IDescriptor* CreateDescriptor() = 0;

}; /* IDescriptorBuilder */

} //namespace description

} //namespace TOOBAD4ML

#endif
