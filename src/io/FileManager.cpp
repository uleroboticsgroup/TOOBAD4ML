#include "FileManager.h"
#include "IOutputFormatStrategy.h"
#include <llvm/Support/raw_ostream.h>
#include <clang/Basic/FileManager.h>
#include <iostream>

using namespace TOOBAD4ML;
using namespace IO;

bool cFileManager::Write(std::vector<std::string> descriptor, IOutputFormatStrategy* strategy, const llvm::Twine& file, bool append) {
    std::cout << "KEEP GOOD" << "\n";
    llvm::raw_ostream *stream;
    std::error_code ec;
    llvm::sys::fs::OpenFlags mode = llvm::sys::fs::F_None;

    std::cout << "KEEP GOOD" << "\n";

    if (append) {
        mode = llvm::sys::fs::F_Append;
    }

    std::cout << "KEEPING GOOD" << "\n";

    if (file.str().empty()) {
        std::cout << "xeKEEP GOOD" << "\n";
        stream = &llvm::outs();
    }
    else {
        std::cout << "xaKEEP GOOD" << "\n";
        stream = new llvm::raw_fd_ostream(llvm::StringRef(file.str()), ec, mode);

    }
    std::cout << "KEEP GOOD" << "\n";
    return strategy->Write(*stream, descriptor) && (ec.value() == 0);
}

std::unique_ptr<cFileManager> cFileManager::m_instance = 0;

cFileManager* cFileManager::GetInstance() {
    if (!m_instance) {
        m_instance = std::unique_ptr<cFileManager>(new cFileManager()); 
    }

    return m_instance.get();
};

cFileManager::cFileManager() {};