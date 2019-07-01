#include "FileManager.h"
#include "IOutputFormatStrategy.h"
#include <llvm/Support/raw_ostream.h>
#include <clang/Basic/FileManager.h>

using namespace TOOBAD4ML;
using namespace IO;

bool cFileManager::Write(std::vector<std::string> descriptor, IOutputFormatStrategy& strategy, const llvm::Twine& file, bool append) {
    std::error_code ec;
    llvm::sys::fs::OpenFlags mode = llvm::sys::fs::F_None;
    if (append) {
        mode = llvm::sys::fs::F_Append;
    }
    
    llvm::raw_fd_ostream stream(llvm::StringRef(file.str()), ec, mode);
    return strategy.Write(stream, descriptor) && (ec.value() == 0);
}

std::unique_ptr<cFileManager> cFileManager::m_instance = 0;

cFileManager* cFileManager::GetInstance() {
    if (!m_instance) {
        m_instance = std::unique_ptr<cFileManager>(new cFileManager()); 
    }

    return m_instance.get();
};

cFileManager::cFileManager() {};
