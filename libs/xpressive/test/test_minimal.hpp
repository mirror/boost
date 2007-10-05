///////////////////////////////////////////////////////////////////////////////
// test_minimal.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_TEST_REGRESS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_TEST_REGRESS_HPP_EAN_10_04_2005

#include <string>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <boost/current_function.hpp>

template<typename T = void>
struct counter
{
    static int value;
};

template<typename T>
int counter<T>::value = 0;

struct execution_aborted
{
};

inline void
report_error(const char *msg, const char *file, int line, const char *func_name, bool is_msg = false)
{
    ++counter<>::value;
    std::cerr << file << "(" << line << "): ";

    if(is_msg)
    {
        std::cerr << msg;
    }
    else
    {
        std::cerr << "test " << msg << " failed";
    }

    if(0 == std::strcmp(func_name, "(unknown)"))
    {
        std::cerr << " in function: '" << func_name << "'";
    }

    std::cerr << std::endl;
}

inline void
report_critical_error(const char *msg, const char *file, int line, const char *func_name, bool is_msg = false)
{
    report_error(msg, file, line, func_name, is_msg);
    throw execution_aborted();
}

#define BOOST_CHECK(exp)                                                        \
    ((exp)                                                                      \
      ? static_cast<void>(0)                                                    \
      : report_error(#exp, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION))

#define BOOST_ERROR(msg_)                                                       \
    report_error((msg_), __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, true)

#define BOOST_REQUIRE(exp)                                                      \
    ((exp)                                                                      \
      ? static_cast<void>(0)                                                    \
      : report_critical_error(#exp, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION))

#define BOOST_FAIL(msg_)                                                        \
    report_critical_error((msg_) ,__FILE__, __LINE__, BOOST_CURRENT_FUNCTION, true)

int test_main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    try
    {
        int run_result = test_main(argc, argv);
        BOOST_CHECK(run_result == 0);
    }
    catch(std::exception const &ex)
    {
        std::string msg = std::string("exception \"") + ex.what() + "\" caught";
        BOOST_ERROR(msg.c_str());
        std::cerr << "\n**** Testing aborted.";
        ++counter<>::value;
    }
    catch(execution_aborted)
    {
        std::cerr << "\n**** Testing aborted.";
        ++counter<>::value;
    }

    if(counter<>::value != 0)
    {
        std::cerr << "\n**** " << counter<>::value
                  << " error" << (counter<>::value > 1 ? "s" : "") << " detected\n";
        return -1;
    }

    std::cout << "\n**** no errors detected\n";
    return 0;
}

#endif
