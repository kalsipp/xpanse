#pragma once

#include <sstream>
#include <iostream>
#include <fstream>
#include <thread>
#include <queue>
#include <mutex>
#include <cstdint>
#include <chrono>
#include <ctime>
#include "helpers.hpp"
// #define NDEBUG
class LoggingFile {
public:
	LoggingFile(const std::string filename, uint8_t verbosity):
		m_filename(filename),
		m_verbosity(verbosity) {
		m_file.open(m_filename);
		std::time_t result = std::time(nullptr);
		m_file << std::ctime(&result) << '\n';
		m_file << "Time \t\t Verbosity \t\t Message\n";
		m_file.close();
	}
	void write(const std::string & text) {
		m_file.open(m_filename, std::ios::app);
		m_file << text << std::endl;
		m_file.close();
	}
	~LoggingFile() {
	}
	std::string m_filename;
	uint8_t m_verbosity;
	std::ofstream m_file;
};

class LogEntry {
public:
	LogEntry(const std::string & text, double timestamp, uint8_t level):
		m_text(text), m_timestamp(timestamp), m_level(level) {}
	std::string m_text;
	double m_timestamp;
	uint8_t m_level;
};

class Logging {
public:
	static void add_file(const std::string & name, uint8_t verbosity);
	static void log(uint8_t level, const std::basic_ostream<char> &);
	static void log(uint8_t level, const std::string &);
	static void teardown();
	static void initialize();
	static const uint8_t TRACE;
	static const uint8_t INFO;
	static const uint8_t WARNING;
	static const uint8_t ERROR;
private:
	Logging();
	static std::string fancify(const LogEntry &);
	static void output_to_terminal(const LogEntry &);
	static void write_loop();
	static bool m_initialized;
	static bool m_running;
	static std::thread m_write_thread;
	static std::vector<LoggingFile*> m_loggingfiles;
	static std::queue<LogEntry> m_write_queue;
	static std::mutex m_mutex;
	static const std::string RED_TEXT;
	static const std::string YELLOW_TEXT;
	static const std::string GREY_TEXT;
	static const std::string RESET_TEXT;
	static std::chrono::high_resolution_clock::time_point m_start_time;
};