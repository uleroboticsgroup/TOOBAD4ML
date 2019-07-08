// ----------------------------------------------------------------------------
#include "analysis/ClangTool.h"
#include "analysis/ModelBOFAction.h"
#include "io/CmdLineArguments.h"
#include "analysis/ModelBOFFrontendActionFactory.h"
#include "io/InputManager.h"
#include <iostream>

// ----------------------------------------------------------------------------

#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>

static llvm::cl::OptionCategory MyToolCategory("MY GOD");

using namespace TOOBAD4ML;

int main(int argc, const char **argv) {

    IO::cInputManager* inputManager = new IO::cInputManager();
    IO::sCmdLineArguments arguments = inputManager->GetSourceFromCommandLine(argc, argv);
    std::vector<std::string> currentSources;

    for (std::string source: arguments.getSources()) {
        currentSources.push_back(source);
        IO::sCmdLineArguments* currentArguments = new IO::sCmdLineArguments(currentSources, arguments.getFlags());

        TOOBAD4ML::analysis::cClangTool tool(*currentArguments);
        
        TOOBAD4ML::analysis::cModelBOFAction* action = new TOOBAD4ML::analysis::cModelBOFAction();
        TOOBAD4ML::analysis::cModelBOFFrontendActionFactory* factory = new TOOBAD4ML::analysis::cModelBOFFrontendActionFactory(*action);
        tool.Run(factory);

        currentSources.pop_back();
    }
   

    return 0;


/*
clang::tooling::CommonOptionsParser OptionsParser(argc, argv,
		MyToolCategory);

clang::tooling::ClangTool Tool(OptionsParser.getCompilations(),
		OptionsParser.getSourcePathList());

int result = Tool.run(
		clang::tooling::newFrontendActionFactory<
				TOOBAD4ML::analysis::cModelBOFAction>().get());
*/
}
