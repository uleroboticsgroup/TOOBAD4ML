#ifndef ANALYSISTEST_BOFACTION_H
#define ANALYSISTEST_BOFACTION_H
#include "iostream"
#include <clang/Frontend/CompilerInstance.h>
#include "analysis/ModelBOFAction.h"

namespace TOOBAD4ML {

namespace analysis {

class cModelBOFActionTestHelper : public cModelBOFAction {

public:

    std::unique_ptr<clang::ASTConsumer> CreateASTConsumerTestHelper(clang::CompilerInstance& CI, llvm::StringRef file){
        return CreateASTConsumer(CI, file);        
    }

};

}

}


#endif