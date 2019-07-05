#include "ModelBOFFrontendActionFactory.h"
#include "ModelBOFAction.h"

//DELETE
#include <iostream>

using namespace TOOBAD4ML;
using namespace analysis;

cModelBOFFrontendActionFactory::cModelBOFFrontendActionFactory(cModelBOFAction& action)
    :m_modelBOFAction(std::unique_ptr<cModelBOFAction>(&action)) {}

clang::FrontendAction* cModelBOFFrontendActionFactory::create() {
    return m_modelBOFAction.get();
}

cModelBOFAction& cModelBOFFrontendActionFactory::GetModelBOFAction() {
    return *(m_modelBOFAction.get());
}
