#ifndef STUBMODELBOFACTION_H
#define STUBMODELBOFACTION_H

#include <analysis/ModelBOFAction.h>

namespace TOOBAD4ML {

namespace analysis {

/*!
 * Stub class to create a mock ModelBOFConsumer.
 */
class cStubModelBOFAction :
    public cModelBOFAction {
public:

    /*!
     *
     *
     * @param
     * @param
     * @return
     */
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
            clang::CompilerInstance&, llvm::StringRef);

}; /* cStubModelBOFAction */

} /* analysis */

} /* TOOBAD4ML */

#endif /* STUBMODELBOFACTION_H */
