#include "CmdLineArguments.h"

using namespace TOOBAD4ML;
using namespace IO;


std::vector<std::string> sCmdLineArguments::getSources() {
    return m_sources;
}

void sCmdLineArguments::setSources(std::vector<std::string> sources) {
    m_sources = sources;
}

std::map<eFlagsType, std::string> sCmdLineArguments::getFlags() {
    return m_flags;
}
void sCmdLineArguments::setFlags(std::map<eFlagsType, std::string> flags) {
    m_flags = flags;
}