#pragma once
#include <random>
#include <chrono>
#include <string>
#include <iostream>
#include <cassert>

#ifndef NDEBUG
/* Blessed https://stackoverflow.com/questions/3767869/adding-message-to-assert */
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion: " #condition << std::endl << \
            "Failed in file: " << __FILE__  << std::endl << \
            "line: " << __LINE__ << std::endl << \
            "Message: " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif


namespace helpers {
uint random_int(int min, int max);
void nice_assert(bool, const std::string &);
std::string get_filename_from_path(const std::string & path);
}