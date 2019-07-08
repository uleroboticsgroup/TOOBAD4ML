#include "FileManager.h"
#include "IOutputFormatStrategy.h"
#include <llvm/Support/raw_ostream.h>
#include <clang/Basic/FileManager.h>
#include <iostream>

using namespace TOOBAD4ML;
using namespace IO;

bool cFileManager::Write(std::vector<std::string> descriptor, IOutputFormatStrategy* strategy, const llvm::Twine& file, bool append) {    
    if (file.str() == "") {
        return strategy->Write(llvm::outs(), descriptor);
    }

    std::error_code ec;
    llvm::sys::fs::OpenFlags mode = llvm::sys::fs::F_None;

    if (append) {
        mode = llvm::sys::fs::F_Append;
    }

    llvm::raw_fd_ostream fd_stream(llvm::StringRef(file.str()), ec, mode);

    int status = strategy->Write(fd_stream, descriptor) && (ec.value() == 0);

    if (status) std::cout << "Results have been written." << "\n";   
    
    fd_stream.close();

    return status;
}

std::unique_ptr<cFileManager> cFileManager::m_instance = 0;

cFileManager* cFileManager::GetInstance() {
    if (!m_instance) {
        m_instance = std::unique_ptr<cFileManager>(new cFileManager()); 
    }

    return m_instance.get();
};

cFileManager::cFileManager() {};