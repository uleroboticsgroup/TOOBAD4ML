#ifndef IO_FILEMANAGER_H_
#define IO_FILEMANAGER_H_
// ------------------------------------------------------------------------
#include <clang/Basic/FileManager.h>
// ------------------------------------------------------------------------
namespace TOOBAD4ML {
namespace IO {

// CLASS FORWARDING
// ----------------------------------------------------------------------------
class IOutputFormatStrategy;

/*!
 * \class cFileManager
 *
 * \brief
 * A utility to write the program's output to the selected destination and format.
 * 
 * \details
 * This class implements a Singleton. It's task is to write the output of the program
 * to the provided file.
 */
class cFileManager {

    // CLASS METHODS
    // ------------------------------------------------------------------------
public:
	bool Write(std::vector<std::string>, IOutputFormatStrategy*, const llvm::Twine&, bool);

	static cFileManager* GetInstance();
private:
	cFileManager();

private:
    // ATTRIBUTES
    // ------------------------------------------------------------------------
	static std::unique_ptr<cFileManager> m_instance;
};


} /* IO */

} /* TOOBAD4ML */

#endif /* IO_FILEMANAGER_H_ */
