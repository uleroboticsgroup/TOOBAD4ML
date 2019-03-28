// ----------------------------------------------------------------------------
#ifndef TOOBAD4ML_DESCRIPTION_DESCRIPTORDECORATOR_H
#define TOOBAD4ML_DESCRIPTION_DESCRIPTORDECORATOR_H
// ----------------------------------------------------------------------------
#include "description/Descriptor.h"
// ----------------------------------------------------------------------------


namespace TOOBAD4ML {

namespace description {

/*!
 * \class cDescriptorDecorator
 *
 * \brief
 *
 *
 * \details
 *
 */
class cDescriptorDecorator : public IDescriptor {

    // CONSTANTS
    // ------------------------------------------------------------------------

public:

    //! Token used for separating features
	const std::string FEATURE_SEPARATOR = ";";


    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------

public:

	/*!
	 *
	 * @param
	 */
	cDescriptorDecorator(IDescriptor*);

	~cDescriptorDecorator();


    // IDESCRIPTOR INHERITED METHODS
    // ------------------------------------------------------------------------

public:

	/*!
	 * Extracts a Buffer Overflow feature from a Code Property Graph.
     *
	 * @param cpg Code Property Graph.
	 * @param bof Buffer Overflow vulnerability present in the CPG.
	 * @return A string of numbers separated by semicolons representing the
     *         feature, or an empty string in case the BOF is not present in
     *         the CPG.
	 */
	virtual std::string ExtractFeature(cCodePropertyGraph&,
			cBufferOverflow&);


    // ATTRIBUTES
    // ------------------------------------------------------------------------

protected:

	//!
	IDescriptor* m_decoratedComponent;

}; /* cDescriptorDecorator */

} // namespace description

} // namespace TOOBAD4ML

#endif
