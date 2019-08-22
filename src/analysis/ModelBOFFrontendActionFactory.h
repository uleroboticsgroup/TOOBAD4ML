#ifndef ANALYSIS_MODELBOFFRONTENDACTIONFACTORY_H
#define ANALYSIS_MODELBOFFRONTENDACTIONFACTORY_H
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