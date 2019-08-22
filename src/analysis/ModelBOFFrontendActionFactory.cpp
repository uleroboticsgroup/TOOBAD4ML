#include "ModelBOFFrontendActionFactory.h"
#include "ModelBOFAction.h"
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace analysis;
// ----------------------------------------------------------------------------
// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------
cModelBOFFrontendActionFactory::cModelBOFFrontendActionFactory(cModelBOFAction& action)
    :m_modelBOFAction(std::unique_ptr<cModelBOFAction>(&action)) {}

// CLASS METHODS
// ----------------------------------------------------------------------------
clang::FrontendAction* cModelBOFFrontendActionFactory::create() {
    return m_modelBOFAction.get();
}

cModelBOFAction& cModelBOFFrontendActionFactory::GetModelBOFAction() {
    return *(m_modelBOFAction.get());
}
