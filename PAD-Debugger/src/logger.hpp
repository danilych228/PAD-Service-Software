/*
 * logger.hpp
 * Simple logging utility for PAD-Debugger
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
};

class Logger {
public:
    /**
     * @brief Log a message with the specified level
     * @param level Log level
     * @param message Message to log
     */
    static void log(LogLevel level, const std::string& message) {
        if (level < min_level_) {
            return;
        }

        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

        std::string level_str;
        switch (level) {
            case LogLevel::DEBUG: level_str = "DEBUG"; break;
            case LogLevel::INFO: level_str = "INFO"; break;
            case LogLevel::WARNING: level_str = "WARNING"; break;
            case LogLevel::ERROR: level_str = "ERROR"; break;
        }

        std::string log_msg = "[" + oss.str() + "] [" + level_str + "] " + message + "\n";

        // Output to console
        if (level >= LogLevel::WARNING || min_level_ <= LogLevel::DEBUG) {
            std::cerr << log_msg;
        } else {
            std::cout << log_msg;
        }

        // Output to file if specified
        if (log_file_.is_open()) {
            log_file_ << log_msg;
            log_file_.flush();
        }
    }

    /**
     * @brief Set the minimum log level to output
     * @param level Minimum level to log
     */
    static void set_level(LogLevel level) {
        min_level_ = level;
    }

    /**
     * @brief Set the log file path
     * @param filepath Path to log file
     */
    static bool set_log_file(const std::string& filepath) {
        log_file_.open(filepath, std::ios::app);
        return log_file_.is_open();
    }

private:
    static LogLevel min_level_;
    static std::ofstream log_file_;
};

// Static member definitions
LogLevel Logger::min_level_ = LogLevel::INFO;
std::ofstream Logger::log_file_;

#endif // LOGGER_HPP