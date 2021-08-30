#include "io/Logger.h"
// ------------------------------------------------------------------------
#include <llvm/Support/raw_os_ostream.h>
#include <clang/Basic/FileManager.h>
#include <ctime>
#include <map>
#include <iostream>
#include <iomanip>
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace IO;

std::unique_ptr<cLogger> cLogger::m_instance = 0;

// CLASS METHODS
// ------------------------------------------------------------------------
cLogger* cLogger::GetInstance() {
    if (!m_instance) {
        m_instance = std::unique_ptr<cLogger>(new cLogger());
    }

    return m_instance.get();
}

std::string formatNumber(int value) {
    return value > 9 ? std::to_string(value) : "0" + std::to_string(value);
}

bool cLogger::Write(eLogLevel level, std::string message) {
    std::map<eLogLevel, std::string> logLevelStrings = {
        {eLogLevel::DEBUG, "DEBUG"},    
        {eLogLevel::INFO, "INFO "},    
        {eLogLevel::WARN, "WARN "},    
        {eLogLevel::ERROR, "ERROR"},    
        {eLogLevel::FATAL, "FATAL"}
    };

    if (level >= m_level) {
        std::error_code ec;
        llvm::sys::fs::OpenFlags mode = llvm::sys::fs::F_Append;

        llvm::raw_fd_ostream fd_stream(llvm::StringRef(m_filename), ec, mode);
        
        time_t *current_time = new time_t;
        struct tm * timeinfo; 
        time(current_time); 
        timeinfo = localtime(current_time);

        fd_stream << formatNumber(timeinfo->tm_mon) << "-" << formatNumber(timeinfo->tm_mday) << "-" << (1900 + timeinfo->tm_year) << " " << formatNumber(timeinfo->tm_hour) << ":" << formatNumber(timeinfo->tm_min) << ":" << formatNumber(timeinfo->tm_sec) << " " << logLevelStrings[level] << "  " << message << "\n"; 

        return true;

    }
    else {
        return false;
    }

}

bool cLogger::SetLogLevel(std::string level) {
    std::map<std::string, eLogLevel> logLevelStrings = {
        {"DEBUG", eLogLevel::DEBUG},    
        {"INFO", eLogLevel::INFO},    
        {"WARN", eLogLevel::WARN},    
        {"ERROR", eLogLevel::ERROR},    
        {"FATAL", eLogLevel::FATAL}
    };

    if (logLevelStrings.count(level) == 0) {
        return false;
    }

    m_level = logLevelStrings[level];
    return true;
}

void cLogger::SetFilename(std::string name) {
    m_filename = name;
}