#ifndef TOOBAD4ML_ANALYSIS_MODELBOFFRONTENDACTIONFACTORY_H
#define TOOBAD4ML_ANALYSIS_MODELBOFFRONTENDACTIONFACTORY_H
// ----------------------------------------------------------------------------
#include <clang/Tooling/Tooling.h>
// ----------------------------------------------------------------------------

namespace TOOBAD4ML {

namespace analysis {
    class cModelBOFAction;

/*!
 * \class cModelBOFFrontendActionFactory
 *
 * \brief
 * A utility to create the BOF Action to be used inside clang.
 *  
 * \details
 * This class implements the Factory pattern.
 * The only task of this class is to create <CODE>TOOBAD4ML::analysis::cModelBOFAction</CODE>
 * objects.
 */
class cModelBOFFrontendActionFactory:
    public clang::tooling::FrontendActionFactory {
    
    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------
public:
    cModelBOFFrontendActionFactory(cModelBOFAction&);

    // INHERITED METHODS
    // ------------------------------------------------------------------------
public:
    clang::FrontendAction* create();

    // ACCESSOR METHODS
    // ------------------------------------------------------------------------
public:
    cModelBOFAction& GetModelBOFAction();

    // ATTRIBUTES
    // ------------------------------------------------------------------------

private:
    std::unique_ptr<cModelBOFAction> m_modelBOFAction;
};

} /* analysis */

} /* TOOBAD4ML */

#endif