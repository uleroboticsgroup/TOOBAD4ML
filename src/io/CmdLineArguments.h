#ifndef IO_CMDLINEARGS_H_
#define IO_CMDLINEARGS_H_

#include <iostream>
#include <vector>
#include <map>
#include "llvm/ADT/Twine.h"

namespace TOOBAD4ML {

namespace IO {

class IOutputFormatStrategy;

enum eFlagsType {
    OUTPUT_FILENAME,
    OUTPUT_EXTENSION
};

/*!
 * \struct sCmdLineArguments
 *
 * \brief
 * A container to hold the data from the program's arguments (sources and flags)
*/

struct sCmdLineArguments {

    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------
public:
    sCmdLineArguments(std::vector<std::string>, std::map<eFlagsType, std::string>);

    // CLASS METHODS
    // ------------------------------------------------------------------------
public:
    llvm::Twine& getFilename();
    IOutputFormatStrategy* getStrategy();

    // ACCESSOR METHODS
    // ------------------------------------------------------------------------
public:
    std::vector<std::string> getSources();
    void setSources(std::vector<std::string>);

    std::map<eFlagsType, std::string> getFlags();
    void setFlags(std::map<eFlagsType, std::string>);

    bool getAppend();
    void setAppend(bool);



    // ATTRIBUTES
    // ------------------------------------------------------------------------
public:
    std::vector<std::string> m_sources;
    std::map<eFlagsType, std::string> m_flags;
    bool m_append;
};

} /* IO */

} /* TOOBAD4ML */

#endif /* IO_CMDLINEARGS_H_ */
