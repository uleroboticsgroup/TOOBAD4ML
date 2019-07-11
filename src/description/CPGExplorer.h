// ----------------------------------------------------------------------------
#ifndef TOOBAD4ML_DESCRIPTION_CPGEXPLORER_H
#define TOOBAD4ML_DESCRIPTION_CPGEXPLORER_H
// ----------------------------------------------------------------------------
#include <llvm/ADT/StringRef.h>
// ----------------------------------------------------------------------------


namespace TOOBAD4ML {

namespace description {


// CLASS FORWARDING
// ----------------------------------------------------------------------------

class IDescriptor;
class cCodePropertyGraph;
class cBufferOverflow;


// CLASS DEFINITION
// ----------------------------------------------------------------------------

/*!
 * \class cCPGExplorer
 *
 * \brief
 * A tool to analyze Code Property Graphs in order to describe Buffer Overflow
 * vulnerabilities.
 *
 * \details
 * This class describes a Buffer Overflow vulnerability by analyzing a {\ref
 * cCodePropertyGraph}. To do so, a descriptor model (see {\ref IDescriptor})
 * is used over the CPG for extracting a set of features. Lastly, the
 * vulnerability is represented as a string of numbers separated by semicolons.
 */
class cCPGExplorer {

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------

public:

	/*!
	 * Creates a Code Property Graph analysis tool.
     *
     * @param descriptor    A model for extracting specific features from the
     *                      CPG.
	 */
	cCPGExplorer(IDescriptor&);

    ~cCPGExplorer();


    // CLASS METHODS
    // ------------------------------------------------------------------------

public:

	/*!
	 * Analyzes a CPG to extract, according to a descriptor, the features of a
     * Buffer Overflow vulnerability.
     *
	 * @param cpg Code Property Graph to be analyzed.
	 * @param bof Buffer Overflow vulnerability to be described.
	 * @return A string of numbers separated by semicolons (where each number
     *         is a feature), that represents a Buffer Overflow vulnerability.
	 */
    std::string Inspect(cCodePropertyGraph&, cBufferOverflow&);


    // ACCESSOR METHODS
    // ------------------------------------------------------------------------

public:

	void SetDescriptor(IDescriptor&);


    // ATTRIBUTES
    // ------------------------------------------------------------------------

private:

    //! Model comprised of several features which together describe a Buffer
    /// Overflow vulnerability
	IDescriptor& m_descriptor;

}; /* class cCPGExplorer */

} // namespace description

} // namespace TOOBAD4ML

// ----------------------------------------------------------------------------
#endif
