// ----------------------------------------------------------------------------
#include "analysis/ClangTool.h"
#include "analysis/ModelBOFAction.h"
#include "io/CmdLineArguments.h"
#include "analysis/ModelBOFFrontendActionFactory.h"
#include "io/InputManager.h"
#include "description/DescriptorFactory.h"
#include "description/Descriptor.h"
#include "io/Logger.h"
// ----------------------------------------------------------------------------

#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>

static llvm::cl::OptionCategory MyToolCategory("TOOBAD4ML");

using namespace TOOBAD4ML;

int main(int argc, const char **argv)
{

    IO::cLogger *logger = IO::cLogger::GetInstance();

    IO::cInputManager *inputManager = new IO::cInputManager();
    IO::sCmdLineArguments arguments = inputManager->GetSourceFromCommandLine(argc, argv);
    TOOBAD4ML::description::cDescriptorFactory descriptionFactory;
    TOOBAD4ML::description::IDescriptor *descriptor = descriptionFactory.CreateDescriptor(arguments.getFlags()[TOOBAD4ML::IO::eFlagsType::DESCRIPTOR_SET]);

    if (!descriptor)
    {
        std::cout << "Invalid descriptor.\nExecution aborted.\n";
        logger->Write(IO::eLogLevel::ERROR, "Invalid descriptor.Execution aborted.");
        return -1;
    }

    std::vector<std::string> currentSources;
    bool firstWrite = true;

    for (std::string source : arguments.getSources())
    {
        logger->Write(IO::eLogLevel::INFO, "Processing file " + source);
        currentSources.push_back(source);
        IO::sCmdLineArguments *currentArguments = new IO::sCmdLineArguments(currentSources, arguments.getFlags());

        if (!firstWrite)
        {
            currentArguments->setAppend(true);
        }
        else
        {
            firstWrite = false;
        }

        TOOBAD4ML::analysis::cClangTool tool(*currentArguments);

        TOOBAD4ML::analysis::cModelBOFAction *action = new TOOBAD4ML::analysis::cModelBOFAction(descriptor);
        TOOBAD4ML::analysis::cModelBOFFrontendActionFactory *factory = new TOOBAD4ML::analysis::cModelBOFFrontendActionFactory(*action);
        tool.Run(factory);

        currentSources.pop_back();
        logger->Write(IO::eLogLevel::INFO, "File processed.");
    }

    logger->Write(IO::eLogLevel::INFO, "Finished.");

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
