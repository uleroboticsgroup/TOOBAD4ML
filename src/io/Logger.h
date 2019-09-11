#ifndef IO_LOGGER_H
#define IO_LOGGER_H
// ------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <memory>
// ------------------------------------------------------------------------

namespace TOOBAD4ML {
namespace IO {

enum eLogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};
// ------------------------------------------------------------------------

/*!
 * \class cLogger
 *
 * \brief
 * A logger that provides information about wha't is happening
 * 
 * \details
 * A singleton implementation of a logger that outputs information
 * of the application to a file.
 * 
 * Structure of the log:
 * MM-DD-YYYY HH:MM:SS LEVEL MESSAGE
 *
 * */
class cLogger {
    // CLASS METHODS
    // ------------------------------------------------------------------------
public:
    static cLogger* GetInstance();
    bool Write(eLogLevel, std::string);
    bool SetLogLevel(std::string); 
    // CONSTRUCTORS & DESTRUCTORS
    // ------------------------------------------------------------------------
private:
    cLogger(): m_level(eLogLevel::INFO) {};

    // ATTRIBUTES
    // ------------------------------------------------------------------------
private:
    static std::unique_ptr<cLogger> m_instance;
    eLogLevel m_level;
};

} /* IO */

} /* TOOBAD4ML */

#endif