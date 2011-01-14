/* test_fisher_f.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/fisher_f_distribution.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/math/distributions/fisher_f.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <vector>
#include <iostream>
#include <numeric>

#include "statistic_tests.hpp"

bool do_test(double m, double n, int max) {
    std::cout << "running fisher_f(" << m << ", " << n << ")" << " " << max << " times: " << std::flush;

    boost::math::fisher_f expected(m, n);
    
    boost::random::fisher_f_distribution<> dist(m, n);
    boost::mt19937 gen;
    kolmogorov_experiment test(max);
    boost::variate_generator<boost::mt19937&, boost::random::fisher_f_distribution<> > vgen(gen, dist);

    double prob = test.probability(test.run(vgen, expected));

    bool result = prob < 0.99;
    const char* err = result? "" : "*";
    std::cout << boost::detail::setprecision(17) << prob << err << std::endl;

    std::cout << boost::detail::setprecision(6);

    return result;
}

bool do_tests(int repeat, double max_m, double max_n, int trials) {
    boost::mt19937 gen;
    boost::uniform_real<> mdist(0.00001, max_m);
    boost::uniform_real<> ndist(0.00001, max_n);
    int errors = 0;
    for(int i = 0; i < repeat; ++i) {
        if(!do_test(mdist(gen), ndist(gen), trials)) {
            ++errors;
        }
    }
    if(errors != 0) {
        std::cout << "*** " << errors << " errors detected ***" << std::endl;
    }
    return errors == 0;
}

int usage() {
    std::cerr << "Usage: test_fisher_f -r <repeat> -m <max m> -n <max n> -t <trials>" << std::endl;
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
    double max_m = 1000.0;
    double max_n = 1000.0;
    int trials = 1000000;

    if(argc > 0) {
        --argc;
        ++argv;
    }
    while(argc > 0) {
        if(argv[0][0] != '-') return usage();
        else if(!handle_option(argc, argv, 'r', repeat)
             && !handle_option(argc, argv, 'm', max_m)
             && !handle_option(argc, argv, 'n', max_n)
             && !handle_option(argc, argv, 't', trials)) {
            return usage();
        }
        --argc;
        ++argv;
    }

    try {
        if(do_tests(repeat, max_m, max_n, trials)) {
            return 0;
        } else {
            return EXIT_FAILURE;
        }
    } catch(...) {
        std::cerr << boost::current_exception_diagnostic_information() << std::endl;
        return EXIT_FAILURE;
    }
}
