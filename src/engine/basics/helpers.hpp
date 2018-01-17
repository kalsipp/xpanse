#pragma once
#include <random>
#include <chrono>
#include <string>
#include <iostream>
#include <cassert>
#include <cmath>
#include <execinfo.h>
#include <unistd.h>
#include <signal.h>
#include <map>
#include "logging.hpp"

void sig_error_handler(int sig);


#ifndef NDEBUG
/* Blessed https://stackoverflow.com/questions/3767869/adding-message-to-assert */
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            Logging::log(Logging::ERROR, std::stringstream() <<std::endl <<  "Assertion: " #condition << std::endl << \
            "Failed in file: " << __FILE__  << std::endl << \
            "line: " << __LINE__ << std::endl << \
            "Message: " << message << std::endl << std::endl); \
            Logging::teardown();\
            sig_error_handler(SIGTERM);\
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif


namespace helpers {
uint random_int(int min, int max);
std::string get_filename_from_path(const std::string & path);
static const double TO_RAD = M_PI / 180;

}