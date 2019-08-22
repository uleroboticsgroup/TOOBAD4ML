/*!\mainpage <H1><CENTER>TOOBAD4ML</CENTER></H1> 
 * 
 * 
 * \section introduction  Description
 *
 *                 A tool for describing buffer overflow vulnerabilities (previously tagged in C source code) in order to further analyze them with Machine Learning techniques.
 * 
 * <BR>
 * 
 *
 *
 * \section getting_started Getting Started
 * 
 *
 *
 *  \subsection prerequisites Prerequisites
 * 
 *  CMake 3.1 or later is required to build the project.
 *  In-source builds are not allowed. So before building TOOBAD4ML you must create a separate directory for the build files.
 *
 *
 *
 * \subsection dependencies Dependencies
 *
 *  The following libraries are used by TOOBAD4ML:
 *
 *  - Clang version 5.0.0 or later;
 *  - Google Test version 1.8.1 or later (only for testing);
 *
 *
 *  You can optionally use Conan to manage these dependencies. However, please note that Clang is not currently available in the official repositories. To get it, you must add the following remote repository before running the conan install command:
 *
 *  \code conan remote add manu343726 https://api.bintray.com/conan/manu343726/conan-packages \endcode
 *  
 *
 *  \subsection installing_conan Installing dependencies with Conan
 *
 *  If you don't plan to use Conan you can ignore this step. Otherwise, first go to the build directory and then type the following command before using CMake:
 *
 *  \code conan install .. --build=missing -s compiler.libcxx=libstdc++11 \endcode
 *
 *  \subsection building Building the project
 *
 *  You can build TOOBAD4ML using your preferred generator, just be sure that you run any CMake commands inside the build directory. For instance, to build with <STRONG>Ninja</STRONG>, type:
 *
 *  \code cmake .. -G "Ninja" \endcode
 *  Note that CMake automatically searches the system for installed dependencies during the configuration process. However, if you want to force it to use Conan's dependencies, simply add the argument <STRONG>-DTOOBAD4ML_FORCE_CONAN=ON</STRONG> to the previous command:
 *
 *  \code cmake .. -G "Ninja" -DTOOBAD4ML_FORCE_CONAN=ON \endcode
 *  Finally, build the project with:
 *
 *  \code cmake --build . \endcode
 *  The binary can be found in the <STRONG><TOOBAD4ML_ROOT_DIR>/bin</STRONG> directory.
 *
 *  \subsection testing Testing the project
 *
 *  Tests can be enabled by adding the argument <STRONG>-DTOOBAD4ML_ENABLE_TESTING=ON </STRONG>to the CMake configuration command:
 *
 *  \code cmake .. -G "Ninja" -DTOOBAD4ML_ENABLE_TESTING=ON \endcode
 *  To build all unit tests, type:
 *
 *  \code cmake --build . --target tests \endcode
 *  It is recommended to run the unit tests with CTest; although all the tests executables can be found in the <STRONG> <TOOBAD4ML_ROOT_DIR>/bin/tests </STRONG> directory. CMake generates the CTest configuration files inside the build directory, so in order to run it just type:
 *
 *  \code ctest -VV \endcode
 *  
 * <BR>
 * \section usage Usage
 *
 * <H3>./TOOBAD4ML <path_to_file_or_to_multiple_files.c> -f=FORMAT -o=FILENAME -- </H3>
 * 
 *  \subsection flags   Flags
 * 
 *  - Format: 
 *      - STD: Standard output
 *      - CSV: CSV format
 * 
 *  - Filename: 
 *      the name of the output file
 * 
 *  <STRONG>NOTE</STRONG>: if filename is provided and format flag is set to <STRONG>STD</STRONG>, filename is ignored.
 *
 *  <BR>
 *  \section faq FAQ
 *
 *  Please check the wiki :-)
 *
 *  <BR>
 *  \section credits Credits
 *
 *  This project has been founded by the Research Institute of Applied Sciences in Cybersecurity (RIASC) from the Universidad de León and developed by:
 *
 *
 *  - Gonzalo Esteban
 *  - Razvan Raducu
 *  - Flavio Rodrigues
 *  - David Fernández
 *
 *
 *  <BR>
 *  \section license License
 *
 *  <H2>TBD :-)</H2>
 * <BR>
 */

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
    bool firstWrite = true;

    for (std::string source: arguments.getSources()) {
        currentSources.push_back(source);
        IO::sCmdLineArguments* currentArguments = new IO::sCmdLineArguments(currentSources, arguments.getFlags());

        if (!firstWrite) {
            currentArguments->setAppend(true);
        }else {
            firstWrite = false;
        }

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
