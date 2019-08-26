// ----------------------------------------------------------------------------
#ifndef TOOBAD4ML_DESCRIPTION_DESCRIPTOR_H
#define TOOBAD4ML_DESCRIPTION_DESCRIPTOR_H
// ----------------------------------------------------------------------------
#include <string>

namespace TOOBAD4ML {

namespace description {


// CLASS FORWARDING
// ----------------------------------------------------------------------------

class cCodePropertyGraph;
class cBufferOverflow;


// CLASS DEFINITION
// ----------------------------------------------------------------------------

/*!
 * \class IDescriptor
 *
 * \brief
 * A description, as a sequence of numbers, of a Buffer Overflow vulnerability.
 *
 * \details
 * This is just the interface for the Decorator design pattern. It declares a
 * single method intended for defining a feature of a Buffer Overflow (BOF).
 * These features are patterns present in the source code, and can be either
 * simple (just one feature) or complex (more than one feature). Features are
 * represented as a string of numbers separated by semicolons and defined by
 * analizing their presence in a {\ref cCodePropertyGraph}.
 */
class IDescriptor {

    // INTERFACE METHODS
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
            cBufferOverflow&) = 0;

	virtual ~IDescriptor() {};

}; /* IDescriptor */

} // namespace description

} // namespace TOOBAD4ML

#endif
