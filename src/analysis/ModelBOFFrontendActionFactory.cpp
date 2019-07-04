#include "ModelBOFFrontendActionFactory.h"
#include "ModelBOFAction.h"

using namespace TOOBAD4ML;
using namespace analysis;

cModelBOFFrontendActionFactory::cModelBOFFrontendActionFactory(cModelBOFAction& action)
    :m_modelBOFAction(action) {}

clang::FrontendAction* cModelBOFFrontendActionFactory::create() {
    return &m_modelBOFAction;
}

cModelBOFAction& cModelBOFFrontendActionFactory::GetModelBOFAction() {
    return m_modelBOFAction;
}
