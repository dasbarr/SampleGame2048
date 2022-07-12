#ifndef UTILS_SIMPLELOGGER_H
#define UTILS_SIMPLELOGGER_H

#include <string>
#include <vector>

namespace sample_game::utils {
    /**
    * Simple logger. Writes messages to log file when program ends.
    */
    class SimpleLogger {
    public:
        ~SimpleLogger() = default;

        /**
         * Adds a regular message to log.
         * @param message Log message.
         */
        static void log(const std::string& message);
        /**
         * Adds a warning message to log.
         * @param message Log message.
         */
        static void warn(const std::string& message);
        /**
         * Adds an error message to log.
         * @param message Log message.
         */
        static void error(const std::string& message);

        /**
         * Writes collected log messages to disk.
         */
        static void flush();

    private:
        static SimpleLogger& instance();

        SimpleLogger() = default;

        /**
         * Adds message to logger internal storage.
         * @param logMessage Log message.
         * @private
         */
        void internalAddMessage(const std::string& logMessage);
        /**
         * Writes collected log messages to disk.
         * @private
         */
        void internalFlush();

        std::vector<std::string> _logMessages;
    };
}

#endif // UTILS_SIMPLELOGGER_H
