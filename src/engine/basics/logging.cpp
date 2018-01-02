#include "logging.hpp"

bool Logging::m_initialized = false;
bool Logging::m_running = false;
std::thread Logging::m_write_thread;
std::vector<LoggingFile*> Logging::m_loggingfiles;
std::queue<LogEntry> Logging::m_write_queue;
std::mutex Logging::m_mutex;

const uint8_t Logging::TRACE = 1;
const uint8_t Logging::INFO = 3;
const uint8_t Logging::WARNING = 5;
const uint8_t Logging::ERROR = 7;
const std::string Logging::RED_TEXT = "\033[0;31m";
const std::string Logging::YELLOW_TEXT = "\033[0;33m";
const std::string Logging::GREY_TEXT = "\033[0;37m";
const std::string Logging::RESET_TEXT = "\033[0m";
std::chrono::high_resolution_clock::time_point Logging::m_start_time;


void Logging::add_file(const std::string & name, uint8_t verbosity) {
	LoggingFile* newlog = new LoggingFile(name, verbosity);
	m_loggingfiles.push_back(newlog);
}

void Logging::log(uint8_t level, const std::basic_ostream<char> & stream) {
#ifndef NDEBUG
	std::stringstream ss;
	ss << stream.rdbuf();
	Logging::log(level, ss.str());
#else
	(void)level;
	(void)stream;
#endif
}

void Logging::log(uint8_t level, const std::string & text) {

#ifndef NDEBUG
	if (!m_initialized) Logging::initialize();
	double duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_start_time).count();
	LogEntry entry(text, duration, level);
	Logging::fancify(entry);
	for (auto it = m_loggingfiles.begin(); it != m_loggingfiles.end(); ++it) {
		if (entry.m_level >= (*it)->m_verbosity) {
			(*it)->write(entry.m_text);
		}
	}
	Logging::output_to_terminal(entry);
#else
	(void)level;
	(void)text;
#endif
}

void Logging::initialize() {
	m_initialized = true;
#ifndef NDEBUG
	m_running = true;
	m_start_time = std::chrono::high_resolution_clock::now();
	// m_write_thread = std::thread(write_loop);
#else
#endif
}

void Logging::teardown() {
	m_running = false;
#ifndef NDEBUG
	// m_write_thread.join();
	for (auto it = m_loggingfiles.begin(); it != m_loggingfiles.end(); ++it) {
		delete *it;
	}
#else
#endif
}

std::string Logging::fancify(const LogEntry & entry) {
	std::string output_string = "";
	output_string += std::to_string(int(entry.m_timestamp)) + "\t\t";
	switch (entry.m_level) {
	case TRACE:
		output_string += "TRACE";
		break;
	case INFO:
		output_string += "INFO";
		break;
	case WARNING:
		output_string += "WARNING";
		break;
	case ERROR:
		output_string += "ERROR";
		break;
	}
	output_string += "\t\t";
	output_string += entry.m_text;
	return output_string;
}

void Logging::output_to_terminal(const LogEntry & entry) {
	switch (entry.m_level) {
	case TRACE:
		break;
	case INFO:
		std::cout << GREY_TEXT << entry.m_text << RESET_TEXT << std::endl;
		break;
	case WARNING:
		std::cout << YELLOW_TEXT << entry.m_text << RESET_TEXT << std::endl;
		break;
	case ERROR:
		std::cerr << RED_TEXT << entry.m_text << RESET_TEXT << std::endl;
		break;
	}
}

void Logging::write_loop() {
	while (m_running || !m_write_queue.empty()) {
		m_mutex.lock();
		if (!m_write_queue.empty()) {
			LogEntry entry = m_write_queue.front();
			m_write_queue.pop();
			m_mutex.unlock();
			entry.m_text = Logging::fancify(entry);
			for (auto it = m_loggingfiles.begin(); it != m_loggingfiles.end(); ++it) {
				if (entry.m_level >= (*it)->m_verbosity) {
					(*it)->write(entry.m_text);
				}
			}
			Logging::output_to_terminal(entry);
		} else {
			m_mutex.unlock();
		}

	}
}

