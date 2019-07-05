// -----------------------------------------------------------------------------
#ifndef  TOOBAD4ML_ANALYSIS_MODELBOFCONSUMER_H
#define  TOOBAD4ML_ANALYSIS_MODELBOFCONSUMER_H
// -----------------------------------------------------------------------------
#include <clang/AST/ASTConsumer.h>
#include <llvm/ADT/Twine.h>
// -----------------------------------------------------------------------------
#include <string>
#include <vector>
// -----------------------------------------------------------------------------


namespace TOOBAD4ML {


// CLASS FORWARDING
// -----------------------------------------------------------------------------

namespace description {

    class cCPGExplorer;
    class IDescriptor;

}

namespace IO {
    class IOutputFormatStrategy;
    class sCmdLineArguments;
}
// CLASS DEFINITION
// -----------------------------------------------------------------------------

namespace analysis {

/*!
 * \class cModelBOFConsumer
 *
 * \brief
 * Models a BOF vulnerability from a given source file.
 *
 * \details
 * This class models a BOF vulnerability by extracting a set of characteristics
 * from a source file. First of all, characteristics are obtained from a set of
 * lines of code present in such file; which can be either vulnerable or not.
 * These lines are indicated as comments, following the convention:
 * "///start_line, start_offset; end_line, end_offset" (without quotes). On the
 * other hand, and in order to extract the characteristics, a model for
 * representing a BOF needs to be previously set (see the
 * <CODE>TOOBAD4ML::description::IDescriptionBuilder</CODE> class). Once this is
 * done, each "tagged" line is processed and a string of numbers is obtained.
 * Consequently, the dataset associated to the given source is comprised of a
 * vector of strings, where each string has a set of numbers representing the
 * selected BOF model.
 */
class cModelBOFConsumer: public clang::ASTConsumer {

    // CONSTRUCTORS & DESTRUCTORS
    // -------------------------------------------------------------------------

public:
	virtual ~cModelBOFConsumer() {}

	/*!
     * Creates the AST consumer object to model BOF vulnerabilities.
	 *
     * @param model Model for describing a BOF using a set of characteristics.
	 */
	cModelBOFConsumer(description::IDescriptor&);


    // clang::ASTConsumer INHERITED METHODS
    // -------------------------------------------------------------------------

public:

	/*!
     * Analyzes the AST of a source file in order to create a BOF representation
     * for each line of code tagged as vulnerable.
	 *
	 * @param context   AST of a given source file.
	 */
	virtual void HandleTranslationUnit(clang::ASTContext&) override;


    // CLASS METHODS
    // -------------------------------------------------------------------------

public:

    bool Output(IO::sCmdLineArguments&);

	//--------- FOR TESTING-----------
	friend class cModelBOFConsumerTest;
	//--------------------------------

    // ACCESSOR METHODS
    // -------------------------------------------------------------------------
    
    void SetModel(description::IDescriptor&);


    // ATTRIBUTES
    // -------------------------------------------------------------------------

private:

    //! Processed lines of code containing the representation of a BOF.
	std::vector<std::string> m_dataset;

    //! Code Property Graph analyzer for obtaining a representation of a BOF.
    description::cCPGExplorer& m_CPGExplorer;

}; /* class cModelBOFConsumer */

//--------- FOR TESTING-----------
class cModelBOFConsumerTest {
public:
	std::vector<std::string> getDataset(cModelBOFConsumer& consumer);
};
//--------------------------------

} /* namespace analysis */

} // namespace TOOBAD4ML

// -----------------------------------------------------------------------------
#endif
