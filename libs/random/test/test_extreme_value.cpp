/* test_extreme_value.cpp
 *
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/extreme_value_distribution.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/math/distributions/extreme_value.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <vector>
#include <iostream>
#include <numeric>

#include "statistic_tests.hpp"

bool do_test(double a, double b, int max) {
    std::cout << "running extreme_value(" << a << ", " << b << ")" << " " << max << " times: " << std::flush;

    boost::math::extreme_value_distribution<> expected(a, b);
    
    boost::random::extreme_value_distribution<> dist(a, b);
    boost::mt19937 gen;
    kolmogorov_experiment test(max);
    boost::variate_generator<boost::mt19937&, boost::random::extreme_value_distribution<> > vgen(gen, dist);

    double prob = test.probability(test.run(vgen, expected));

    bool result = prob < 0.99;
    const char* err = result? "" : "*";
    std::cout << std::setprecision(17) << prob << err << std::endl;

    std::cout << std::setprecision(6);

    return result;
}

bool do_tests(int repeat, double max_a, double max_b, int trials) {
    boost::mt19937 gen;
    boost::uniform_real<> adist(0.00001, max_a);
    boost::uniform_real<> bdist(0.00001, max_b);
    int errors = 0;
    for(int i = 0; i < repeat; ++i) {
        if(!do_test(adist(gen), bdist(gen), trials)) {
            ++errors;
        }
    }
    if(errors != 0) {
        std::cout << "*** " << errors << " errors detected ***" << std::endl;
    }
    return errors == 0;
}

int usage() {
    std::cerr << "Usage: test_extreme_value -r <repeat> -a <max a> -b <max b> -t <trials>" << std::endl;
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
    double max_a = 1000.0;
    double max_b = 1000.0;
    int trials = 1000000;

    if(argc > 0) {
        --argc;
        ++argv;
    }
    while(argc > 0) {
        if(argv[0][0] != '-') return usage();
        else if(!handle_option(argc, argv, 'r', repeat)
             && !handle_option(argc, argv, 'a', max_a)
             && !handle_option(argc, argv, 'b', max_b)
             && !handle_option(argc, argv, 't', trials)) {
            return usage();
        }
        --argc;
        ++argv;
    }

    try {
        if(do_tests(repeat, max_a, max_b, trials)) {
            return 0;
        } else {
            return EXIT_FAILURE;
        }
    } catch(...) {
        std::cerr << boost::current_exception_diagnostic_information() << std::endl;
        return EXIT_FAILURE;
    }
}
