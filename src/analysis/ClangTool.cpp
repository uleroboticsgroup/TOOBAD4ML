// ----------------------------------------------------------------------------
#include "io/InputManager.h"
#include "analysis/ClangTool.h"
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/CompilationDatabase.h>

// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace analysis;


// OTHER STUFF
// ----------------------------------------------------------------------------

// set some options to show when asking for help about the tool
static llvm::cl::OptionCategory toolCategory("TOOBAD4ML options");
static llvm::cl::extrahelp CommonHelp(
        clang::tooling::CommonOptionsParser::HelpMessage
);


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cClangTool::cClangTool(int argc, const char** argv) : m_tool(NULL) {
    // argc must be at least 2 (including program name), in order to parse the
    // contents of argv
    assert(argc > 1);

    clang::tooling::CommonOptionsParser optionsParser(
            argc, argv, toolCategory
    );

    m_tool = new clang::tooling::ClangTool(
            optionsParser.getCompilations(),
            optionsParser.getSourcePathList()
    );
}


cClangTool::cClangTool(const llvm::Twine& path) : m_tool(NULL) {
    llvm::ArrayRef<std::string> cmdLineArgs;
    clang::tooling::FixedCompilationDatabase compilations(
            path,
            cmdLineArgs
    );

    m_tool = new clang::tooling::ClangTool(
            compilations,
            compilations.getAllFiles()
    );
}


cClangTool::~cClangTool() {
    delete m_tool;
}


// METHODS
// ----------------------------------------------------------------------------

int cClangTool::Run(clang::tooling::ToolAction* action) {
    return m_tool->run(action);

}

bool cClangToolTest::checkIfClangToolExists(cClangTool &tool) {
    return tool.m_tool != nullptr;
}