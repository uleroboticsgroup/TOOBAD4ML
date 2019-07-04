// ----------------------------------------------------------------------------
#include "analysis/ClangTool.h"
#include "analysis/ModelBOFAction.h"
#include "analysis/ModelBOFConsumer.h"
#include "analysis/ModelBOFFrontendActionFactory.h"
#include "description/PadmanabhuniBuilder.h"

// ----------------------------------------------------------------------------

#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CommonOptionsParser.h>

static llvm::cl::OptionCategory MyToolCategory("MY GOD");

int main(int argc, const char **argv) {

    TOOBAD4ML::analysis::cClangTool tool(argc, argv);
    
    TOOBAD4ML::analysis::cModelBOFAction* action = new TOOBAD4ML::analysis::cModelBOFAction();
    TOOBAD4ML::analysis::cModelBOFFrontendActionFactory* factory = new TOOBAD4ML::analysis::cModelBOFFrontendActionFactory(*action);

    return tool.Run(factory);



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
