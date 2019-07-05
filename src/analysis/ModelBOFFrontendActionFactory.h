#ifndef ANALYSIS_MODELBOFFRONTENDACTIONFACTORY_H
#define ANALYSIS_MODELBOFFRONTENDACTIONFACTORY_H

#include <clang/Tooling/Tooling.h>

namespace TOOBAD4ML {

namespace analysis {

class cModelBOFAction;

class cModelBOFFrontendActionFactory:
    public clang::tooling::FrontendActionFactory {

public:
    cModelBOFFrontendActionFactory(cModelBOFAction&);
    clang::FrontendAction* create();
    cModelBOFAction& GetModelBOFAction();

private:
    std::unique_ptr<cModelBOFAction> m_modelBOFAction;
};

}

}

#endif