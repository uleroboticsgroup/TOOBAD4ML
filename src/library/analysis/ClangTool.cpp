// ----------------------------------------------------------------------------
#include "analysis/ClangTool.h"
// ----------------------------------------------------------------------------
#include <llvm/Support/CommandLine.h>
#include "ModelBOFAction.h"
#include "io/IOutputFormatStrategy.h"
#include "io/CmdLineArguments.h"
#include "io/InputManager.h"
#include "analysis/ModelBOFFrontendActionFactory.h"

// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace analysis;
// ----------------------------------------------------------------------------
// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

//cClangTool::cClangTool(int argc, const char** argv)
//    : cClangTool(IO::cInputManager::GetSourceFromCommandLine(argc, argv)) {}

cClangTool::cClangTool(IO::sCmdLineArguments& cmdLineArgs)
    : m_args(cmdLineArgs) {
        IO::cInputManager* inputManager = new IO::cInputManager();
        m_compilationDB = std::unique_ptr<clang::tooling::CompilationDatabase>(inputManager->GetCompilationDatabase(cmdLineArgs.getSources()[0]));
        m_tool = std::unique_ptr<clang::tooling::ClangTool>(new clang::tooling::ClangTool(*m_compilationDB, cmdLineArgs.getSources()));
      }

cClangTool::~cClangTool() {
    m_tool.reset();
    m_compilationDB.reset();
}


// CLASS METHODS
// ----------------------------------------------------------------------------

int cClangTool::Run(clang::tooling::ToolAction* action) {
    llvm::Twine filename = m_args.getFilename();
    IO::IOutputFormatStrategy* strategy = m_args.getStrategy();
    cModelBOFFrontendActionFactory* BOFFactory = static_cast<cModelBOFFrontendActionFactory*>(action);
    BOFFactory->GetModelBOFAction().setCmdLineArguments(m_args);
    int result = m_tool->run(action);
    return result;
}

bool cClangToolTest::checkIfClangToolExists(cClangTool &tool) {
    return tool.m_tool != nullptr;
}