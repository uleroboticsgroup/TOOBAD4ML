#ifndef IO_FILEMANAGER_H_
#define IO_FILEMANAGER_H_

#include <llvm/ADT/StringRef.h>
#include <clang/Basic/FileManager.h>

namespace TOOBAD4ML {

namespace IO {

class IOutputFormatStrategy;

typedef std::vector<llvm::StringRef> KeywordList;

class cFileManager {

public:

	KeywordList Read(std::string);
	
	bool Write(std::vector<std::string>, IOutputFormatStrategy&, const llvm::Twine&, bool);

	void SetWorkingDirectory(llvm::StringRef);

	static cFileManager* GetInstance();

private:
	cFileManager();
	static std::unique_ptr<cFileManager> m_instance;
//	clang::FileManager m_fileManager;
};


}
}

#endif /* IO_FILEMANAGER_H_ */
