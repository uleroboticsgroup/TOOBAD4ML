// ----------------------------------------------------------------------------
#include "analysis/ClangTool.h"
// ----------------------------------------------------------------------------
#include <llvm/Support/CommandLine.h>
#include "ModelBOFAction.h"
#include "io/FormatStrategyFactory.h"
#include "io/IOutputFormatStrategy.h"
#include "io/CmdLineArguments.h"
#include "io/InputManager.h"
#include "analysis/ModelBOFFrontendActionFactory.h"
#include "io/FileManager.h"

#include "iostream"
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace analysis;
// ----------------------------------------------------------------------------
// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cClangTool::cClangTool(int argc, const char** argv)
    : cClangTool(IO::cInputManager::GetSourceFromCommandLine(argc, argv)) {}

cClangTool::cClangTool(IO::sCmdLineArguments& cmdLineArgs)
    : m_compilationDB(IO::cInputManager::GetCompilationDatabase(cmdLineArgs.getSources()[0])),
      m_tool(new clang::tooling::ClangTool(*m_compilationDB, cmdLineArgs.getSources())),
      m_args(cmdLineArgs) {
        std::cout << m_args.getFlags().size() << "\n";
      }

cClangTool::~cClangTool() {
    m_tool.reset();
    m_compilationDB.reset();
}


// CLASS METHODS
// ----------------------------------------------------------------------------

int cClangTool::Run(clang::tooling::ToolAction* action) {
    int result = m_tool->run(action);

    IO::cFileManager* fm = IO::cFileManager::GetInstance();
    IO::cFormatStrategyFactory* fsFactory = new IO::cFormatStrategyFactory();
    IO::IOutputFormatStrategy* strategy;

    std::cout << m_args.getFlags().size() << "\n";
    std::cout << m_args.getFlags().count(IO::eFlagsType::OUTPUT_EXTENSION) << "\n";
    std::cout << m_args.getFlags().count(IO::eFlagsType::OUTPUT_FILENAME) << "\n";

    IO::eOutputFormatType type = fsFactory->getOutputFormatType(m_args.getFlags().at(IO::eFlagsType::OUTPUT_EXTENSION));
    llvm::Twine* filename = new llvm::Twine(m_args.getFlags().at(IO::eFlagsType::OUTPUT_FILENAME));

    if (type == IO::eOutputFormatType::CSV) {
        strategy = &fsFactory->CreateCSVOutputFormatStrategy(); 
    }
    else if(type == IO::eOutputFormatType::STD) {
        strategy = &fsFactory->CreateSTDOutputFormatStrategy();
    }
    else {
        return result;
    }


    cModelBOFFrontendActionFactory* BOFFactory = static_cast<cModelBOFFrontendActionFactory*>(action);

    std::cout << "WTF" << "\n";
    BOFFactory->GetModelBOFAction().getModelBOFConsumer()->Output(*strategy, *filename);
    std::cout << "WTF" << "\n";
    return result;
}

bool cClangToolTest::checkIfClangToolExists(cClangTool &tool) {
    return tool.m_tool != nullptr;
}