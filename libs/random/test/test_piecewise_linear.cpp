/* test_piecewise_linear.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/piecewise_linear_distribution.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <vector>
#include <iostream>
#include <numeric>

#include "chi_squared_test.hpp"

bool do_test(int n, long long max) {
    std::cout << "running piecewise_linear(p0, p1, ..., p" << n-1 << ")" << " " << max << " times: " << std::flush;

    std::vector<double> weights;
    std::vector<double> expected;
    {
        boost::mt19937 egen;
        for(int i = 0; i < n; ++i) {
            weights.push_back(egen());
        }
        for(int i = 0; i < n - 1; ++i) {
            expected.push_back((weights[i] + weights[i + 1]) / 2);
        }
        double sum = std::accumulate(expected.begin(), expected.end(), 0.0);
        for(std::vector<double>::iterator iter = expected.begin(), end = expected.end(); iter != end; ++iter) {
            *iter /= sum;
        }
    }
    std::vector<double> intervals;
    for(int i = 0; i < n; ++i) {
        intervals.push_back(i);
    }
    
    boost::random::piecewise_linear_distribution<> dist(intervals, weights);
    boost::mt19937 gen;
    std::vector<long long> results(expected.size());
    for(long long i = 0; i < max; ++i) {
        ++results[static_cast<std::size_t>(dist(gen))];
    }

    long long sum = std::accumulate(results.begin(), results.end(), 0ll);
    if(sum != max) {
        std::cout << "*** Failed: incorrect total: " << sum << " ***" << std::endl;
        return false;
    }
    double chsqr = chi_squared_test(results, expected, max);

    bool result = chsqr < 0.99;
    const char* err = result? "" : "*";
    std::cout << boost::detail::setprecision(17) << chsqr << err << std::endl;

    std::cout << boost::detail::setprecision(6);

    return result;
}

bool do_tests(int repeat, int max_n, long long trials) {
    boost::mt19937 gen;
    boost::uniform_int<> idist(1, max_n);
    int errors = 0;
    for(int i = 0; i < repeat; ++i) {
        if(!do_test(idist(gen), trials)) {
            ++errors;
        }
    }
    if(errors != 0) {
        std::cout << "*** " << errors << " errors detected ***" << std::endl;
    }
    return errors == 0;
}

int usage() {
    std::cerr << "Usage: test_piecewise_linear -r <repeat> -n <max n> -t <trials>" << std::endl;
    return 2;
}

template<class T>
bool handle_option(int& argc, char**& argv, char opt, T& value) {
    if(argv[0][1] == opt && argc > 1) {
        --argc;
        ++argv;
        value = boost::lexical_cast<T>(argv[0]);
        return true;
    } else {
        return false;
    }
}

int main(int argc, char** argv) {
    int repeat = 10;
    int max_n = 100000;
    long long trials = 1000000ll;

    if(argc > 0) {
        --argc;
        ++argv;
    }
    while(argc > 0) {
        if(argv[0][0] != '-') return usage();
        else if(!handle_option(argc, argv, 'r', repeat)
             && !handle_option(argc, argv, 'n', max_n)
             && !handle_option(argc, argv, 't', trials)) {
            return usage();
        }
        --argc;
        ++argv;
    }

    try {
        if(do_tests(repeat, max_n, trials)) {
            return 0;
        } else {
            return EXIT_FAILURE;
        }
    } catch(...) {
        std::cerr << boost::current_exception_diagnostic_information() << std::endl;
        return EXIT_FAILURE;
    }
}
