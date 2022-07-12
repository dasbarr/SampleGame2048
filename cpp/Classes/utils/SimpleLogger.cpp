#include "SimpleLogger.h"
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <iostream>

sample_game::utils::SimpleLogger& sample_game::utils::SimpleLogger::instance() {
    static SimpleLogger loggerInstance;
    return loggerInstance;
}

void sample_game::utils::SimpleLogger::log(const std::string& message) {
    // generate timestamp string
    std::stringstream timestampSStream;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    timestampSStream << std::put_time(&tm, "[%d.%m.%Y %H:%M:%S] ") << std::endl;

    instance().internalAddMessage(timestampSStream.str() + message);
}

void sample_game::utils::SimpleLogger::warn(const std::string& message) {
    log("WARNING: " + message);
}

void sample_game::utils::SimpleLogger::error(const std::string& message) {
    log("ERROR: " + message);
}

void sample_game::utils::SimpleLogger::flush() {
    instance().internalFlush();
}

void sample_game::utils::SimpleLogger::internalAddMessage(const std::string& logMessage) {
    _logMessages.push_back(logMessage);
}

void sample_game::utils::SimpleLogger::internalFlush() {
    if (_logMessages.empty())
        return; // nothing to flush

    // at first flush replace log file
    static bool discardPrevLogFile = true;
    auto logFileOpenMode = discardPrevLogFile ? std::ios_base::trunc : std::ios_base::app;

    std::ofstream logFile;
    logFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // write to file
    try {
        logFile.open("log.txt", std::ios_base::out | logFileOpenMode);

        for (auto& logMessage : _logMessages) {
            logFile << logMessage << std::endl;
        }

        logFile.close();

        // next flushes should add data to the end of log file
        discardPrevLogFile = false;
    }
    catch (std::ofstream::failure& writeError) {
        std::cerr << "Exception occurred when writing to the log file\n" << std::endl;
    }
}
