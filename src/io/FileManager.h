#ifndef IO_FILEMANAGER_H_
#define IO_FILEMANAGER_H_

#include <llvm/ADT/StringRef.h>

namespace TOOBAD4ML {

namespace io {

class cFileManager {

public:

	KeywordList Read(std::string);

	void SetWorkingDirectory(llvm::StringRef);

	static cFileManager* GetInstance();

private:

	cFileManager();

	std::unique_ptr<cFileManager> m_instance;
	clang::FileManager m_fileManager;

	~cFileManager();

};

typedef std::vector<llvm::StringRef> KeywordList;

}
}

#endif /* IO_FILEMANAGER_H_ */
