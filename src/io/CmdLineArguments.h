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


struct sCmdLineArguments {
    std::vector<std::string> m_sources;
    std::map<eFlagsType, std::string> m_flags;
    bool m_append;

    std::vector<std::string> getSources();
    void setSources(std::vector<std::string>);

    std::map<eFlagsType, std::string> getFlags();
    void setFlags(std::map<eFlagsType, std::string>);

    bool getAppend();
    void setAppend(bool);
    
    llvm::Twine& getFilename();
    IOutputFormatStrategy* getStrategy();

    sCmdLineArguments(std::vector<std::string> sources, std::map<eFlagsType, std::string> flags):
        m_sources(sources),
        m_flags(flags),
        m_append(false) {}
};

}

}

#endif /* IO_CMDLINEARGS_H_ */
